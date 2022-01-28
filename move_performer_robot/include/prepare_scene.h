#ifndef SCENE
#define SCENE

#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include "generics.h"

#define Table1           "table1"
#define Table2           "table2"
#define Barrier          "barrier"

#define TableXCenter    0.5
#define TableYCenter    0.0

#define TableXSize       0.2
#define TableYSize       0.5
#define TableZSize       0.4

#define BlockSize        0.05

#define BarrierXCenter   0.0
#define BarrierYCenter   -0.5

#define BarrierXSize     0.4
#define BarrierYSize     0.2
#define BarrierZSize     0.4

#define FristPosition    0.2
#define SecondPosition   0.0
#define ThirdPosition    -0.2


enum class Stack_Num {One, Two, Three};

string to_string(Stack_Num sn);

double get_position(Stack_Num sn);

Stack_Num get_Stack_Num(int i);

class Scene{

public:
  Scene();
  
  void addCubes(Stack_Num, unsigned int, string, int);
private:
  void addTable(string, string, double, double, double, double, double, double);
  
  moveit::planning_interface::PlanningSceneInterface *psi;

  std::vector<moveit_msgs::CollisionObject> collision_objects_run_time_added;
  std::vector<moveit_msgs::CollisionObject> collision_objects_initial_scene;
  
};
#endif
