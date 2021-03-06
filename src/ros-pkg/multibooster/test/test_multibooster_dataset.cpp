#include <multibooster/multibooster.h>
#include <multibooster/synth_data.h>
#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

using namespace Eigen;
using namespace std;

TEST(Object, serialization)
{
  srand(time(NULL));
  SynthDatasetGenerator sdg;
  sdg.feature_probability_ = 1;
  MultiBoosterDataset* mbd = sdg.generateDataset();
  Object& obj0 = *mbd->objs_[0];
  

  ofstream ofile;
  ofile.open("object");
    
  timeval start, end;
  gettimeofday(&start, NULL);
  obj0.serialize(ofile);
  gettimeofday(&end, NULL);
  double elapsed = end.tv_sec * 1000. + end.tv_usec / 1000. - (start.tv_sec * 1000. + start.tv_usec / 1000.);
  cout << elapsed << " ms to serialize." << endl;
  ofile.close();
    
  ifstream ifile;
  ifile.open("object");
  gettimeofday(&start, NULL);
  Object obj1(ifile);
  gettimeofday(&end, NULL);
  elapsed = end.tv_sec * 1000. + end.tv_usec / 1000. - (start.tv_sec * 1000. + start.tv_usec / 1000.);
  cout << elapsed << " ms to deserialize." << endl;
  ifile.close();

  EXPECT_TRUE(obj1.equals(obj0));

  
//   cout << obj0.descriptors_.size() << " " << obj1.descriptors_.size() << endl;
//   cout << obj0.label_ << " " << obj1.label_ << endl;
//   cout << obj0.descriptors_[0].vector->transpose() << endl;
//   cout << obj1.descriptors_[0].vector->transpose() << endl;
//   cout << obj0.descriptors_[1].vector->transpose() << endl;
//   cout << obj1.descriptors_[1].vector->transpose() << endl;

  
  boost::filesystem::remove("object");
  delete mbd;
}

TEST(MultiBoosterDataset, saveAndLoadConsistency) {

  srand(time(NULL));
  SynthDatasetGenerator sdg;
  MultiBoosterDataset* mbd = sdg.generateDataset();
  mbd->save("test.mbd");
  MultiBoosterDataset mbd2("test.mbd");
  EXPECT_TRUE(mbd->compare(mbd2));

  MultiBoosterDataset* mbd3 = sdg.generateDataset();
  EXPECT_FALSE(mbd->compare(*mbd3));
//   cout << mbd->status() << endl;
//   cout << mbd2.status() << endl;
//   cout << mbd3->status() << endl;
  delete mbd;
  delete mbd3;
}

TEST(MultiBoosterDataset, copyConsistency) {
  srand(0);
  SynthDatasetGenerator sdg;
  MultiBoosterDataset* mbd = sdg.generateDataset(); 
  MultiBoosterDataset mbd2(*mbd);
  EXPECT_TRUE(mbd->compare(mbd2));
  delete mbd;
}

TEST(MultiBoosterDataset, applyMappingSimple) {
  srand(0);
  SynthDatasetGenerator sdg;
  sdg.num_objs_ = 30;
  sdg.num_bg_ = 30;
  MultiBoosterDataset* mbd1 = sdg.generateDataset();
  MultiBoosterDataset copy(*mbd1);
  NameMapping cm = mbd1->class_map_;
  NameMapping fm = mbd1->feature_map_;
  vector<string> classes = cm.getIdToNameMapping();
  vector<string> feature_spaces = fm.getIdToNameMapping();
  classes.push_back("Added_Class");
  feature_spaces.push_back("Added_feature_space");
  NameMapping cm2(classes);
  NameMapping fm2(feature_spaces);
  mbd1->applyNewMappings(cm2, fm2);

  for(size_t m=0; m<mbd1->objs_.size(); ++m) { 
    EXPECT_TRUE(mbd1->objs_[m]->descriptors_.size() == feature_spaces.size());
  }
  EXPECT_TRUE(mbd1->num_objs_of_class_.size() == classes.size());
  EXPECT_TRUE(mbd1->ymc_.rows() == (int)classes.size());
  EXPECT_TRUE(mbd1->num_bg_ == copy.num_bg_);

  NameTranslator class_tr(copy.class_map_, mbd1->class_map_);
  for(size_t c=0; c<(size_t)copy.ymc_.rows(); ++c) {
    EXPECT_TRUE(copy.num_objs_of_class_[c] == mbd1->num_objs_of_class_[class_tr.toMap2(c)]);
    for(size_t m=0; m<copy.objs_.size(); ++m) {
      EXPECT_TRUE(copy.ymc_(c,m) == mbd1->ymc_(class_tr.toMap2(c), m));
    }
  }
  delete mbd1;
}  

TEST(MultiBoosterDataset, join) {
  srand(0);
  //MultiBoosterDataset* generateDataset(size_t num_objs, size_t num_feature_spaces, size_t num_classes, size_t num_dims, double variance) {
  SynthDatasetGenerator sdg;
  sdg.num_objs_ = 30;
  sdg.num_bg_ = 30;
  sdg.num_classes_ = 2;
  sdg.num_feature_spaces_ = 5;
  MultiBoosterDataset* mbd1 = sdg.generateDataset(); 
  sdg.num_classes_ = 10;
  sdg.num_feature_spaces_ = 15;
  MultiBoosterDataset* mbd2 = sdg.generateDataset(); 
  MultiBoosterDataset copy(*mbd1);

//   cout << "***" << endl;
//   cout << mbd1->status() << endl;
//   cout << mbd1->class_map_.serialize() << endl;
//   cout << "***" << endl;
//   cout << mbd2->status() << endl;
//   cout << mbd2->class_map_.serialize() << endl;
  mbd1->join(*mbd2);
//   cout << "***" << endl;
//   cout << mbd1->status() << endl;
//   cout << mbd1->class_map_.serialize() << endl;
//   cout << "***" << endl;


  NameTranslator class_tr(copy.class_map_, mbd1->class_map_);
  NameTranslator feature_tr(copy.feature_map_, mbd1->feature_map_);
  for(size_t c=0; c<(size_t)copy.ymc_.rows(); ++c) {
    for(size_t m=0; m<(size_t)copy.ymc_.cols(); ++m) {
      EXPECT_TRUE(copy.ymc_(c,m) == mbd1->ymc_(class_tr.toMap2(c), m));
      if(copy.objs_[m]->label_ == -1)
	EXPECT_TRUE(mbd1->objs_[m]->label_ == -1);
      else
	EXPECT_TRUE((size_t)copy.objs_[m]->label_ == class_tr.toMap1(mbd1->objs_[m]->label_));
      vector<descriptor>& d1 = copy.objs_[m]->descriptors_;
      vector<descriptor>& d2 = mbd1->objs_[m]->descriptors_;
      for(size_t d=0; d<d1.size(); ++d) {
	size_t idx = feature_tr.toMap2(d);
	if(!d1[d].vector)
	  EXPECT_TRUE(d2[idx].vector == NULL);
	else
	  EXPECT_TRUE(d2[idx].vector != NULL);
	if(d1[d].vector && d2[idx].vector) {
	  EXPECT_TRUE(*d1[d].vector == *d2[idx].vector);
	  EXPECT_TRUE(d1[d].length_squared == d2[idx].length_squared);
	}
      }
    }
  }
  
  
//   for(size_t i=0; i<mbd1->objs_.size(); ++i) {
//     cout << "ndesc " << mbd1->objs_[i]->descriptors_.size() << endl;
//     cout << mbd1->objs_[i]->status(mbd1->class_map_, mbd1->feature_map_) << endl;
//   }

  delete mbd1;
  delete mbd2;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
