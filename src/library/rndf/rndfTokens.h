#ifndef RNDF_RNDFTOKENS_H
#define RNDF_RNDFTOKENS_H

#include <string.h>

typedef enum {
  RNDF_START,
  SRNDF,
  RNDF_NAME,
  NUM_SEGMENTS,
  NUM_ZONES,
  NUM_INTERSECTIONS,
  OPTIONAL_FILE_HEADER,
  SEGMENT,
  NUM_LANES,
  OPTIONAL_SEGMENT_HEADER,
  LANE,
  NUM_WAYPOINTS,
  OPTIONAL_LANE_HEADER,
  LANE_WAYPOINT,
  END_LANE,
  END_SEGMENT,
  ZONE,
  NUM_SPOTS,
  OPTIONAL_ZONE_HEADER,
  PERIMETER,
  NUM_PERIMETERPOINTS,
  OPTIONAL_PERIMETER_HEADER,
  ZONE_WAYPOINT,
  END_PERIMETER,
  SPOT,
  OPTIONAL_SPOT_HEADER,
  SPOT_WAYPOINT,
  END_SPOT,
  END_ZONE,
  END_FILE,
  NUM_CROSSWALKS,
  CROSSWALK,
  CROSSWALK_WIDTH,
  CROSSWALK_P1,
  CROSSWALK_P2,
  END_CROSSWALK,
  INTERSECTION,
  TRAFFICLIGHT,
  OPTIONAL_LIGHT_HEADER,
  LIGHT_POSITION,
  END_TRAFFICLIGHT,
  END_INTERSECTION,
  NUM_TRAFFICLIGHTS,
} rndf_state_t, *rndf_state_p;

char *rndf_state_name[] = {
  "RNDF_START",
  "SRNDF",
  "RNDF_NAME",
  "NUM_SEGMENTS",
  "NUM_ZONES",
  "OPTIONAL_FILE_HEADER",
  "SEGMENT",
  "NUM_LANES",
  "OPTIONAL_SEGMENT_HEADER",
  "LANE",
  "NUM_WAYPOINTS",
  "OPTIONAL_LANE_HEADER",
  "LANE_WAYPOINT",
  "END_LANE",
  "END_SEGMENT",
  "ZONE",
  "NUM_SPOTS",
  "OPTIONAL_ZONE_HEADER",
  "PERIMETER",
  "NUM_PERIMETERPOINTS",
  "OPTIONAL_PERIMETER_HEADER",
  "ZONE_WAYPOINT",
  "END_PERIMETER",
  "SPOT",
  "OPTIONAL_SPOT_HEADER",
  "SPOT_WAYPOINT",
  "END_SPOT",
  "END_ZONE",
  "END_FILE",
};

typedef struct {
  rndf_state_t state1;
  std::string command;
  rndf_state_t state2;
} legal_rndf_command_t, *legal_rndf_command_p;

legal_rndf_command_t legal_rndf_command[] = {
  {RNDF_START, "SRNDF", SRNDF},
  {SRNDF, "RNDF_name", RNDF_NAME},
  {RNDF_START, "RNDF_name", RNDF_NAME},
  {RNDF_NAME, "num_segments", NUM_SEGMENTS},
  {NUM_SEGMENTS, "num_zones", NUM_ZONES},
  {NUM_SEGMENTS, "num_intersections", NUM_INTERSECTIONS},
  {NUM_ZONES, "num_intersections", NUM_INTERSECTIONS},
  {NUM_ZONES, "format_version", OPTIONAL_FILE_HEADER},
  {NUM_ZONES, "segment", SEGMENT},
  {NUM_ZONES, "zone", ZONE},
  {NUM_ZONES, "intersection", END_FILE},
  {NUM_ZONES, "end_file", END_FILE},
  {NUM_INTERSECTIONS, "format_version", OPTIONAL_FILE_HEADER},
  {NUM_INTERSECTIONS, "segment", SEGMENT},
  {NUM_INTERSECTIONS, "zone", ZONE},
  {NUM_INTERSECTIONS, "intersection", END_FILE},
  {NUM_INTERSECTIONS, "end_file", END_FILE},
  {OPTIONAL_FILE_HEADER, "format_version", OPTIONAL_FILE_HEADER},
  {OPTIONAL_FILE_HEADER, "creation_date", OPTIONAL_FILE_HEADER},
  {OPTIONAL_FILE_HEADER, "id_string", OPTIONAL_FILE_HEADER},
  {OPTIONAL_FILE_HEADER, "rndf_lib_version", OPTIONAL_FILE_HEADER},
  {OPTIONAL_FILE_HEADER, "segment", SEGMENT},
  {OPTIONAL_FILE_HEADER, "zone", ZONE},
  {OPTIONAL_FILE_HEADER, "end_file", END_FILE},
  {SEGMENT, "num_lanes", NUM_LANES},
  {NUM_LANES, "num_crosswalks", NUM_CROSSWALKS},
  {NUM_LANES, "segment_name", OPTIONAL_SEGMENT_HEADER},
  {NUM_LANES, "speed_limit", OPTIONAL_SEGMENT_HEADER},
  {NUM_LANES, "lane", LANE},
  {NUM_LANES, "end_segment", END_SEGMENT},
  {NUM_CROSSWALKS, "segment_name", OPTIONAL_SEGMENT_HEADER},
  {NUM_CROSSWALKS, "speed_limit", OPTIONAL_SEGMENT_HEADER},
  {NUM_CROSSWALKS, "lane", LANE},
  {NUM_CROSSWALKS, "end_segment", END_SEGMENT},
  {OPTIONAL_SEGMENT_HEADER, "lane", LANE},
  {OPTIONAL_SEGMENT_HEADER, "speed_limit", OPTIONAL_SEGMENT_HEADER},
  {LANE, "num_waypoints", NUM_WAYPOINTS},
  {NUM_WAYPOINTS, "lane_width", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "left_boundary", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "right_boundary", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "checkpoint", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "stop", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "exit", OPTIONAL_LANE_HEADER},
  {NUM_WAYPOINTS, "waypoint", LANE_WAYPOINT},
  {NUM_WAYPOINTS, "end_lane", END_LANE},
  {OPTIONAL_LANE_HEADER, "lane_width", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "lane_type", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "left_boundary", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "right_boundary", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "checkpoint", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "stop", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "cross", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "light", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "exit", OPTIONAL_LANE_HEADER},
  {OPTIONAL_LANE_HEADER, "waypoint", LANE_WAYPOINT},
  {OPTIONAL_LANE_HEADER, "end_lane", END_LANE},
  {LANE_WAYPOINT, "waypoint", LANE_WAYPOINT},
  {LANE_WAYPOINT, "end_lane", END_LANE},
  {END_LANE, "lane", LANE},
  {END_LANE, "crosswalk", CROSSWALK},
  {END_LANE, "end_segment", END_SEGMENT},
  {CROSSWALK, "crosswalk_width", CROSSWALK_WIDTH},
  {CROSSWALK_WIDTH, "crosswalk_p1", CROSSWALK_P1},
  {CROSSWALK_P1, "crosswalk_p2", CROSSWALK_P2},
  {CROSSWALK_P2, "end_crosswalk", END_CROSSWALK},
  {END_CROSSWALK, "crosswalk", CROSSWALK},
  {END_CROSSWALK, "end_segment", END_SEGMENT},
  {END_SEGMENT, "segment", SEGMENT},
  {END_SEGMENT, "zone", ZONE},
  {END_SEGMENT, "intersection", INTERSECTION},
  {END_SEGMENT, "end_file", END_FILE},
  {ZONE, "num_spots", NUM_SPOTS},
  {NUM_SPOTS, "zone_name", OPTIONAL_ZONE_HEADER},
  {NUM_SPOTS, "perimeter", PERIMETER},
  {OPTIONAL_ZONE_HEADER, "perimeter", PERIMETER},
  {PERIMETER, "num_perimeterpoints", NUM_PERIMETERPOINTS},
  {NUM_PERIMETERPOINTS, "exit", OPTIONAL_PERIMETER_HEADER},
  {NUM_PERIMETERPOINTS, "waypoint", ZONE_WAYPOINT},
  {NUM_PERIMETERPOINTS, "end_perimeter", END_PERIMETER},
  {OPTIONAL_PERIMETER_HEADER, "exit", OPTIONAL_PERIMETER_HEADER},
  {OPTIONAL_PERIMETER_HEADER, "waypoint", ZONE_WAYPOINT},
  {OPTIONAL_PERIMETER_HEADER, "end_perimeter", END_PERIMETER},
  {ZONE_WAYPOINT, "waypoint", ZONE_WAYPOINT},
  {ZONE_WAYPOINT, "end_perimeter", END_PERIMETER},
  {END_PERIMETER, "spot", SPOT},
  {END_PERIMETER, "end_zone", END_ZONE},
  {SPOT, "spot_width", OPTIONAL_SPOT_HEADER},
  {SPOT, "checkpoint", OPTIONAL_SPOT_HEADER},
  {OPTIONAL_SPOT_HEADER, "spot_width", OPTIONAL_SPOT_HEADER},
  {OPTIONAL_SPOT_HEADER, "checkpoint", OPTIONAL_SPOT_HEADER},
  {OPTIONAL_SPOT_HEADER, "waypoint", SPOT_WAYPOINT},
  {SPOT_WAYPOINT, "waypoint", SPOT_WAYPOINT},
  {SPOT_WAYPOINT, "end_spot", END_SPOT},
  {END_SPOT, "spot", SPOT},
  {END_SPOT, "end_zone", END_ZONE},
  {END_ZONE, "zone", ZONE},
  {END_ZONE, "end_file", END_FILE},
  {END_ZONE, "intersection", INTERSECTION},
  {INTERSECTION, "num_trafficlights", NUM_TRAFFICLIGHTS},
  {NUM_TRAFFICLIGHTS, "trafficlight", TRAFFICLIGHT},
  {TRAFFICLIGHT, "group_id", OPTIONAL_LIGHT_HEADER},
  {TRAFFICLIGHT, "position", LIGHT_POSITION},
  {OPTIONAL_LIGHT_HEADER, "position", LIGHT_POSITION},
  {LIGHT_POSITION, "end_trafficlight", END_TRAFFICLIGHT},
  {END_TRAFFICLIGHT, "end_intersection", END_INTERSECTION},
  {END_TRAFFICLIGHT, "trafficlight", TRAFFICLIGHT},
  {END_INTERSECTION, "end_file", END_FILE},
};

#endif // RNDF_RNDFTOKENS_H