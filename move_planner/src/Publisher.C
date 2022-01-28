#include "Publisher.h"

Publisher::Publisher(ros::NodeHandle *nh){

  n = nh;
  init_pub = new ros::Publisher(n->advertise<std_msgs::String>("init_config", 1000));

  act_pub = new ros::Publisher(n->advertise<std_msgs::String>("action", 1000));
};

void Publisher::publish_initial_config(vector<string> &initially){

  std_msgs::String msg;
  for(auto el : initially){


    msg.data = el;
    cerr << "*******" << msg.data << "******" << endl;
    init_pub->publish(msg);
    ros::spinOnce();
  }
    
};

void Publisher::publish_action(string &action){
  
  cerr << "*******" << action << "******" << endl;
  std_msgs::String msg;

  msg.data = action;
  act_pub->publish(msg);
  ros::spinOnce();
  this_thread::sleep_for(seconds{10});

};
