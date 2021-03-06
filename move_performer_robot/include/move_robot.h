#ifndef MOVE_GROUP
#define MOVE_GROUP

#include "generics.h"
#include "prepare_scene.h"
#include <moveit/move_group_interface/move_group_interface.h>

class Move_Group{

 public:

  Move_Group(int i);
  void pick(string, string, Stack_Num, unsigned int);
  
  void pick_from_barrier(string);
  
  void place_on_barrier(string);
  
  void place(string, string, Stack_Num, unsigned int);
 private:

  moveit::planning_interface::MoveGroupInterface *move_group;
  int robot_i;
  string frame_id;
  
  void openGripper(trajectory_msgs::JointTrajectory&);

  void closedGripper(trajectory_msgs::JointTrajectory&);
};
#endif
