#ifndef ACTION_MANAGER
#define ACTION_MANAGER

#include "Publisher.h"

#define AGENT1 string("robot1")
#define AGENT2 string("robot2")

#define init_initially1_file string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/classical_input/initiallyRobot1.A")
#define init_initially2_file string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/classical_input/initiallyRobot2.A")
#define c_domain_file        string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/classical_input/domain.A")
#define e_domain_file        string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/epistemic_input/domain.epddl")
#define e_istance_file       string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/epistemic_input/pb1.epddl")
#define e_context_file       string(getenv("HOME"))+string("/catkin_ws/src/move_planner/input/context/contextEx.epddl")
#define results              string("results.txt")

class ActionManager{

public:

  ActionManager(bool, string, ros::NodeHandle *);
  
  void handle_peek(string);

  void handle_pspb(string, string);

  void handle_pbps(string, string, string);
  
  vector<string> action_robot_vector;
  vector<string> init_robot_vector;
  

private:
  
  void generate_finally(string);
  
  void generate_and_run_lp(string);
  
  void initially_collect(int);

  void insert_barrier_info();
  
  void read_classic_output(vector<string> &, vector<pair<string,int>> &, int);

  void push_action(string, int);
  
  void write_initially(string, vector<string> &);

  bool free_barrier;
  string on_barrier;

  ros::NodeHandle *n;
  ros::ServiceClient *client;

  Publisher *P;
  
  stringstream classical_world_status_1;
  stringstream classical_world_status_2;

  stringstream classical_domain;
  
  string barrier;
  string finally;

  string asp_to_add = "\nh(1..3). \n block(white;blue;green;yellow;red;black;orange;table). \n place(1..3).\n";
};

#endif
