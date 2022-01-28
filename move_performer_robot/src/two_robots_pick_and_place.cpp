/* Author: Davide Solda'*/

// ROS
#include <ros/ros.h>

// Scene handler
#include "prepare_scene.h"

// Moves handler
#include "move_robot.h"

// Messages
#include "std_msgs/String.h"

using namespace std;
using namespace std::chrono;

Scene *scene;
Move_Group *move_group1;
Move_Group *move_group2;


void init_msg_handler (const std_msgs::String::ConstPtr& msg){

  cout << msg->data.c_str() << endl;

  string smsg {msg->data.c_str()};
  stringstream m;
  m << smsg;
  //color; stack; height; robotID
  //red;   1;     0;      1
  vector<string> mv;
  string tmp;

  while(getline(m,tmp,';')){
    mv.push_back(tmp);
  }
  
  string color = mv[0];
  
  Stack_Num s = get_Stack_Num(atoi(mv[1].c_str()));
  int height = atoi(mv[2].c_str())-1;
  int robot_ID = atoi(mv[3].c_str());

  if (color != "table")
    scene->addCubes(s, height, color, robot_ID);
}


vector<string> actions;
mutex m;

bool g_ready = false;
int g_data = 0;



void action_handler(const std_msgs::String::ConstPtr& msg){

  string action = msg->data.c_str();

  unique_lock<mutex> lck(m);
  actions.push_back(action);  
  lck.unlock();

  cerr << action << endl;
    
}


void executer() {
  while (true) {

    while (actions.size() == 0) {
      this_thread::sleep_for(seconds{1});
    }
    
    unique_lock<mutex> lck(m);
    string action = actions[0];
    actions.erase(actions.begin());
    lck.unlock();

   stringstream ssaction;
   ssaction << action;
   vector<string> mv;
   string tmp;

   while(getline(ssaction,tmp,';')){
     mv.push_back(tmp);
   }

   int robot_ID = atoi(mv[mv.size()-1].c_str());
   Move_Group *g = (robot_ID == 1) ? move_group1 : move_group2;

   string color = mv[1];

  
   if(mv[0] == "put_on_barrier")
     g->place_on_barrier(color);
   else if(mv[0] == "pick_from_barrier")
     g->pick_from_barrier(color);
   else{
     
     Stack_Num sn = get_Stack_Num(atoi(mv[4].c_str()));
     int height = atoi(mv[3].c_str())-1;
     string base_color = mv[2];
     if (base_color == "table") base_color = (robot_ID == 1) ? Table1 : Table2;
     if(mv[0] == "pick")
       g->pick(color, base_color, sn, height);
     
     else if(mv[0] == "put")
       g->place(color, base_color, sn, height);
   } 
  }
}


int main(int argc, char** argv){

  ros::init(argc, argv, "panda_arm_pick_place");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  scene = new Scene();
  move_group1 = new Move_Group(1);
  move_group2 = new Move_Group(2);

  ros::WallDuration(1.0).sleep();
  
  ros::Subscriber sub_init = nh.subscribe("init_config", 1000, init_msg_handler);

  ros::Subscriber sub_action = nh.subscribe("action", 1000, action_handler);

  thread ex {executer};
  ros::waitForShutdown();
  
  return 0;
}
