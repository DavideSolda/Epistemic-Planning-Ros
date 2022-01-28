#include "generics.h"
#include "action_manager.h"

int main(int argc, char **argv){

  ros::init(argc, argv, "PlanningPublisher");

  ros::NodeHandle *n = new ros::NodeHandle;
  //generate the EFP istance:
  
  string cmd = "python EpistemicPlanning/architecture.py " + e_domain_file + " " + e_istance_file + " " + e_context_file;
  system(cmd.c_str());

  //launch the EFP solver:
  system("efp.out EpistemicPlanning/Output/EFP/domain_pb1.tmp > EpistemicPlanning/EpistemicActions/actions.txt");

  std::ifstream input("EpistemicPlanning/EpistemicActions/actions.txt");
  std::string eactions;
  for( std::string line; getline( input, line ); ){

    if(string::npos != line.find("Executed actions"))

      eactions = line.substr(18, line.size()-1);
  }

  //splitting the actions
  string tmp; 
  stringstream ss(eactions);
  vector<string> action_vector;

  bool first = true;
  while(getline(ss, tmp, ',')){
    if (first){
      action_vector.push_back(tmp);
      first = false;
    }else
      action_vector.push_back(tmp.substr(1,tmp.size()-1));
  }

  //tokenizing the acitons
  vector<vector<string>> tokenized_action_vector (action_vector.size());
  
  for (int i=0; i<action_vector.size(); i++){
    stringstream ss(action_vector[i]);
    first = true;
    while(getline(ss, tmp, '_')){
      tokenized_action_vector[i].push_back(tmp);
    }
  }

  //to visualize the tokenized action list
  for (auto x : tokenized_action_vector){

    for (auto y : x){

      cout << y << " ";
    }
    cout << endl;
  }

  //manage the different actions
  //peek robot2 yellow 
  //pspb robot2 yellow 
  //pbps robot1 robot2 yellow

  ActionManager AM(true, "", n);
  
  for (auto a : tokenized_action_vector){

    if(a[0] == "peek") AM.handle_peek(a[1]);
    else if(a[0] == "pspb") AM.handle_pspb(a[1], a[2]);
    else if(a[0] == "pbps") AM.handle_pbps(a[1], a[2], a[3]);
  }


  cout << "*********************************************" << endl;
  for(auto el : AM.action_robot_vector)
    cout << el << endl;
  for(auto el : AM.init_robot_vector)
    cout << el << endl;

  cout << "*********************************************" << endl;


  ros::spin();

}
