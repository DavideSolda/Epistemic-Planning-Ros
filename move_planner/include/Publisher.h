#ifndef PUBLISHER
#define PUBLISHER
#include "generics.h"

class Publisher{

 public:
  Publisher(ros::NodeHandle *);
  void publish_initial_config(vector<string> &);
  void publish_action(string &);
 private:
  ros::Publisher *init_pub;
  ros::Publisher *act_pub;
  ros::NodeHandle *n;
};
#endif
