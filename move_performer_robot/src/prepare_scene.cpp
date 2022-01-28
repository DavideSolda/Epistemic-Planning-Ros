#include "prepare_scene.h"

using namespace std;

string to_string(Stack_Num sn){

  switch (sn){

    case Stack_Num::One : return "One";
    case Stack_Num::Two : return "Two";
    default             : return "Three";
  }
}

double get_position(Stack_Num sn){
 switch (sn){

  case Stack_Num::One   : return FristPosition;
  case Stack_Num::Two   : return SecondPosition;
  default               : return ThirdPosition;
 }
}

Stack_Num get_Stack_Num(int i){
  if(i==1) return Stack_Num::One;
  if(i==2) return Stack_Num::Two;
  return Stack_Num::Three;
}

Scene::Scene(){

  psi = new moveit::planning_interface::PlanningSceneInterface;

  addTable(Table1,  "panda1_link0", TableXSize,     TableYSize,     TableZSize,
	                            TableXCenter,   TableYCenter,   TableZSize/2);
  addTable(Table2,  "panda2_link0", TableXSize,     TableYSize,     TableZSize,
	                            TableXCenter,   TableYCenter,   TableZSize/2);
  addTable(Barrier, "panda1_link0", BarrierXSize,   BarrierYSize,   BarrierZSize,
	                            BarrierXCenter, BarrierYCenter, BarrierZSize/2);

  this_thread::sleep_for(seconds{2});
  psi->applyCollisionObjects(collision_objects_initial_scene);

}

void Scene::addCubes(Stack_Num sn, unsigned int height, string cube_name, int robot_i){

  // Add the first table where the cube will originally be kept.
  moveit_msgs::CollisionObject collision_object;
  collision_object.header.frame_id = "panda"+to_string(robot_i)+"_link0";
  
  shape_msgs::SolidPrimitive primitive;
  geometry_msgs::Pose box_pose;

  collision_object.id = cube_name;

  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = BlockSize;
  primitive.dimensions[1] = BlockSize;
  primitive.dimensions[2] = BlockSize;

  box_pose.orientation.w = 1;
  box_pose.position.y = get_position(sn); 
  box_pose.position.x = TableXCenter;
  box_pose.position.z = TableZSize + BlockSize/2  + BlockSize*height;
    
  collision_object.primitives.push_back(primitive);
  collision_object.primitive_poses.push_back(box_pose);

  collision_object.operation = collision_object.ADD;

  collision_objects_run_time_added.push_back(collision_object);
  psi->applyCollisionObjects(collision_objects_run_time_added);

}

void Scene::addTable(string name, string frame_id, double dimx, double dimy, double dimz, double x, double y, double z){

  moveit_msgs::CollisionObject collision_object;

  collision_object.id = name;
  collision_object.header.frame_id = frame_id;

  collision_object.primitives.resize(1);
  collision_object.primitives[0].type = collision_object.primitives[0].BOX;
  collision_object.primitives[0].dimensions.resize(3);
  collision_object.primitives[0].dimensions[0] = dimx;
  collision_object.primitives[0].dimensions[1] = dimy;
  collision_object.primitives[0].dimensions[2] = dimz;

  collision_object.primitive_poses.resize(1);
  collision_object.primitive_poses[0].position.x = x;
  collision_object.primitive_poses[0].position.y = y;
  collision_object.primitive_poses[0].position.z = z;

  collision_object.operation = collision_object.ADD;

  collision_objects_initial_scene.push_back(collision_object);
  
  psi->applyCollisionObjects(collision_objects_initial_scene);
}
