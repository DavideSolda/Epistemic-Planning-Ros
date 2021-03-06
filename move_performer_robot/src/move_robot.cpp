#include "move_robot.h"


Move_Group::Move_Group(int i):robot_i{i}{

  
  frame_id = "panda"+to_string(i)+"_link0";

  move_group = new moveit::planning_interface::MoveGroupInterface("panda"+to_string(i)+"_arm");

  //move_group->setPlanningTime(1000.0);

  //move_group->setPlannerId("RRTConnectConfigDefault");

}
void Move_Group::pick(string color, string base_color, Stack_Num sn, unsigned int h){

  vector<moveit_msgs::Grasp> grasps;
  grasps.resize(1);

  grasps[0].grasp_pose.header.frame_id = frame_id;

  grasps[0].grasp_pose.pose.orientation.x = 0.923955699469;
  grasps[0].grasp_pose.pose.orientation.y = -0.382499497279;
  grasps[0].grasp_pose.pose.orientation.z = 1.3249325839e-12;
  grasps[0].grasp_pose.pose.orientation.w = 3.20041176635e-12;
  
  grasps[0].grasp_pose.pose.position.x = TableXCenter;
  grasps[0].grasp_pose.pose.position.y = get_position(sn);
  grasps[0].grasp_pose.pose.position.z = TableZSize + BlockSize*(h+1) + .1;

  grasps[0].pre_grasp_approach.direction.header.frame_id = frame_id;

  grasps[0].pre_grasp_approach.direction.vector.z = -1.0;
  grasps[0].pre_grasp_approach.min_distance = 0.095;
  grasps[0].pre_grasp_approach.desired_distance = 0.115;

  grasps[0].post_grasp_retreat.direction.header.frame_id = frame_id;

  grasps[0].post_grasp_retreat.direction.vector.z = 1.0;
  grasps[0].post_grasp_retreat.min_distance = 0.1;
  grasps[0].post_grasp_retreat.desired_distance = 0.25;


  openGripper(grasps[0].pre_grasp_posture);

  closedGripper(grasps[0].grasp_posture);

  move_group->setSupportSurfaceName(base_color);
    
  move_group->pick(color, grasps);

}
  
void Move_Group::pick_from_barrier(string color){

  vector<moveit_msgs::Grasp> grasps;
  grasps.resize(1);
    
  grasps[0].grasp_pose.header.frame_id = frame_id;
    
  grasps[0].grasp_pose.pose.orientation.x = 0.923837314308;
  grasps[0].grasp_pose.pose.orientation.y = 0.382785219993;
  grasps[0].grasp_pose.pose.orientation.z = 4.30758422588e-05;
  grasps[0].grasp_pose.pose.orientation.w = 0.000300317790124;
    
  grasps[0].grasp_pose.pose.position.x = 0;
  grasps[0].grasp_pose.pose.position.y = BarrierYCenter;
  grasps[0].grasp_pose.pose.position.z = TableZSize + BlockSize/2 + 0.1 ;
  
  grasps[0].pre_grasp_approach.direction.header.frame_id = frame_id;

  grasps[0].pre_grasp_approach.direction.vector.z = -1.0;

  grasps[0].pre_grasp_approach.min_distance = 0.095;
  grasps[0].pre_grasp_approach.desired_distance = 0.115;

  grasps[0].post_grasp_retreat.direction.header.frame_id = frame_id;

  grasps[0].post_grasp_retreat.direction.vector.z = 1.0;
  grasps[0].post_grasp_retreat.direction.vector.y = 1.0;
  grasps[0].post_grasp_retreat.min_distance = 0.2;
  grasps[0].post_grasp_retreat.desired_distance = 0.25;
    
  openGripper(grasps[0].pre_grasp_posture);

  closedGripper(grasps[0].grasp_posture);

    
  move_group->setSupportSurfaceName(Barrier);
    
  move_group->pick(color, grasps);
    
}
  
void Move_Group::place_on_barrier(string color){

  vector<moveit_msgs::PlaceLocation> place_location;
  place_location.resize(1);

  place_location[0].place_pose.header.frame_id = frame_id;

  place_location[0].place_pose.pose.position.x = BarrierXCenter;
  place_location[0].place_pose.pose.position.y = BarrierYCenter;
  place_location[0].place_pose.pose.position.z = TableZSize + BlockSize/2;
    
  place_location[0].pre_place_approach.direction.header.frame_id = frame_id;
    
  place_location[0].pre_place_approach.direction.vector.z = -1.0;
  place_location[0].pre_place_approach.min_distance = 0.095;
  place_location[0].pre_place_approach.desired_distance = 0.115;
    
  place_location[0].post_place_retreat.direction.header.frame_id = frame_id;
  
  place_location[0].post_place_retreat.direction.vector.z = 1.0;
  place_location[0].post_place_retreat.direction.vector.y = 1.0;
  place_location[0].post_place_retreat.min_distance = 0.2;
  place_location[0].post_place_retreat.desired_distance = 0.25;
    
  openGripper(place_location[0].post_place_posture);
    
  move_group->setSupportSurfaceName(Barrier);
    
  move_group->place(color, place_location);
    
}
  
void Move_Group::place(string color, string base_color, Stack_Num sn, unsigned int h){

  vector<moveit_msgs::PlaceLocation> place_location;
  place_location.resize(1);
    
  place_location[0].place_pose.header.frame_id = frame_id;
    
  place_location[0].place_pose.pose.position.x = TableXCenter;
  place_location[0].place_pose.pose.position.y = get_position(sn);
  place_location[0].place_pose.pose.position.z = TableZSize + BlockSize/2 + BlockSize*h;
  
  place_location[0].pre_place_approach.direction.header.frame_id = frame_id;
    
  place_location[0].pre_place_approach.direction.vector.z = -1;
  place_location[0].pre_place_approach.min_distance = 0.095;
  place_location[0].pre_place_approach.desired_distance = 0.115;
    
  place_location[0].post_place_retreat.direction.header.frame_id = frame_id;

  place_location[0].post_place_retreat.direction.vector.z = 1;
  place_location[0].post_place_retreat.min_distance = 0.1;
  place_location[0].post_place_retreat.desired_distance = 0.25;
    
    
  openGripper(place_location[0].post_place_posture);
  
  move_group->setSupportSurfaceName(base_color);
  
  move_group->place(color, place_location);

}

void Move_Group::openGripper(trajectory_msgs::JointTrajectory& posture){

  posture.joint_names.resize(2);
  posture.joint_names[0] = "panda"+to_string(robot_i)+"_finger_joint1";
  posture.joint_names[1] = "panda"+to_string(robot_i)+"_finger_joint2";

  posture.points.resize(1);
  posture.points[0].positions.resize(2);
  posture.points[0].positions[0] = 0.04;
  posture.points[0].positions[1] = 0.04;
  
  posture.points[0].time_from_start = ros::Duration(0.2);

}

void Move_Group::closedGripper(trajectory_msgs::JointTrajectory& posture){

  posture.joint_names.resize(2);
  posture.joint_names[0] = "panda"+to_string(robot_i)+"_finger_joint1";
  posture.joint_names[1] = "panda"+to_string(robot_i)+"_finger_joint2";

  posture.points.resize(1);
  posture.points[0].positions.resize(2);
  posture.points[0].positions[0] = 0.025;
  posture.points[0].positions[1] = 0.025;

  posture.points[0].time_from_start = ros::Duration(0.1);

}  
