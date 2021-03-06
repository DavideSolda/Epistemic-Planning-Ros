#include "action_manager.h"

ActionManager::ActionManager(bool f_b, string o_b, ros::NodeHandle *nh): free_barrier{f_b}, on_barrier{o_b}{

  n = nh;

  ifstream init_file1(init_initially1_file);
  classical_world_status_1 << init_file1.rdbuf();

  ifstream init_file2(init_initially2_file);
  classical_world_status_2 << init_file2.rdbuf();

  ifstream dom(domain_file);
  classical_domain << dom.rdbuf();

  //cerr << "domain: " << endl;
  //cerr << classical_domain.str() << endl;
  P = new Publisher(n);

  initially_collect(1);
  initially_collect(2);

  this_thread::sleep_for(seconds{1});
  P->publish_initial_config(init_robot_vector);

  client = new ros::ServiceClient(n->serviceClient<custom_msgs::Compilation>("compileA"));
  client->waitForExistence();


}

void ActionManager::handle_peek(string agent){

  cerr << "Agent " << agent << " is looking at his blocks.\n";

}

void ActionManager::handle_pspb(string agent, string color){

  cerr << "Agent " << agent << " is picking from its stack color " << color << " to place it on the barrier.\n";

  finally = "finally barrier(" + color + ").\n";

  generate_and_run_lp(agent);

  vector<string> initially_vector;
  vector<pair<string,int>> action_vector;
  read_classic_output(initially_vector, action_vector, atoi(agent.substr(agent.size()-1,1).c_str()));

  write_initially(agent, initially_vector);

}

void ActionManager::handle_pbps(string agent_recevier, string agent_giver, string color){

  cout << "Agent " << agent_recevier << " is picking from the barrier color " << color << ", placed there by agent " << agent_giver << ".\n";

  finally = "finally top(" + color + ", 1).";

  generate_and_run_lp(agent_recevier);

  vector<string> initially_vector;
  vector<pair<string,int>> action_vector;
  read_classic_output(initially_vector, action_vector, atoi(agent_recevier.substr(agent_recevier.size()-1,1).c_str()));

  write_initially(agent_recevier, initially_vector);

}

void ActionManager::generate_and_run_lp(string agent){

  barrier =  free_barrier ? "initially free_barrier." : "initially barrier(" + on_barrier + ").";

  stringstream &a_istance = (agent == AGENT1) ? classical_world_status_1 : classical_world_status_2;

  custom_msgs::Compilation srv;
  
  srv.request.data.data = a_istance.str() + "\n" + barrier + "\n" + classical_domain.str() + finally;
  client->call(srv);

  string asp_istance = srv.response.data.data + asp_to_add;

  //cerr << "asp_istance:" << endl;
  //cerr << asp_istance << endl;
  ofstream f("lp_temp.lp");
  f << asp_istance;
  f.close();
  string cmd = "clingo lp_temp.lp | tail -10 | head -1 > " + results;
  cerr << cmd << endl;
  //system("cat lp_temp.lp");
  system(cmd.c_str());
  system(("cat "+results).c_str());
}

void ActionManager::initially_collect(int agent_i){

  stringstream &initially = (agent_i == 1) ? classical_world_status_1 : classical_world_status_2;
  string tmp;
  vector<string> stack1;
  vector<string> stack2;
  vector<string> stack3;
  vector<string> collect_on;
  while (getline(initially, tmp)){

      /*
      initially free_gripper.
      initially on(green,red).
      initially top(green,1).
      initially top(blue,2).
      initially hight(1,2).
      initially hight(2,1).
      initially hight(3,0).
      */

    if(tmp.size()>10){
      tmp = tmp.substr(10, (tmp.size()-1)-10);
      
      if(tmp.substr(0,3) ==  "top"){
	int id = atoi(tmp.substr(tmp.size()-2,1).c_str());

	string top_color = tmp.substr(4,tmp.size()-7);
	if(id == 1)
	  stack1.push_back(top_color);
	else if(id == 2)
	  stack2.push_back(top_color);
	else if(id == 3)
	  stack3.push_back(top_color);
      }else if(tmp.substr(0,2) ==  "on")
	collect_on.push_back(tmp);
      
    }
  }


  for (int i = 0; i < collect_on.size(); i++){

    for (auto el : collect_on){//for example: on(green,red)
      int comma = el.find(",");
      int closep = el.find(")");
      string col1 = el.substr(3,comma-3);
      string col2 = el.substr(comma+1,closep-(comma+1));
        
      if(stack1.size()>0 && stack1[stack1.size()-1]==col1) stack1.push_back(col2);
      if(stack2.size()>0 && stack2[stack2.size()-1]==col1) stack2.push_back(col2);
      if(stack3.size()>0 && stack3[stack3.size()-1]==col1) stack3.push_back(col2);
    }
  }

  reverse(stack1.begin(), stack1.end());
  reverse(stack2.begin(), stack2.end());
  reverse(stack3.begin(), stack3.end());

  cerr << "stack1" << endl;
  for (auto el : stack1)
    cerr << el << endl;

  cerr << "stack2" << endl;
  for (auto el : stack2)
    cerr << el << endl;

  cerr << "stack3" << endl;
  for (auto el : stack3)
    cerr << el << endl;
    
  for(int i = 0; i<stack1.size(); i++)
    init_robot_vector.push_back(stack1[i]+";1;"+to_string(i)+";"+to_string(agent_i));
  
  for(int i = 0; i<stack2.size(); i++)
    init_robot_vector.push_back(stack2[i]+";2;"+to_string(i)+";"+to_string(agent_i));
  
  for(int i = 0; i<stack3.size(); i++)
    init_robot_vector.push_back(stack3[i]+";3;"+to_string(i)+";"+to_string(agent_i));
}

void ActionManager::read_classic_output(vector<string> &initially_vector, vector<pair<string,int>> &action_vector, int agent_i){

  ifstream f (results);
  string tmp;
  while (getline(f,tmp,' ')){
    if(tmp.substr(0,6) == "occurs"){
      if(tmp.substr(7,4) != "noop"){      // action
	action_vector.push_back(make_pair(tmp.substr(7, (tmp.size()-4)-6),
					  // order number
					  atoi(tmp.substr(tmp.size()-2,1).c_str())));
      }
    }else{
      if(tmp.substr(6,3) != "neg"){
	
	string fluent = tmp.substr(6,(tmp.size()-1)-6);
	initially_vector.push_back(fluent);

	if(fluent == "free_barrier"){

	  free_barrier = true;
	  on_barrier = "";
	    
	}else if(fluent.substr(0,7) == "barrier" ){//check if barrier(yellow)

	  free_barrier = false;
	  on_barrier = fluent.substr(8, fluent.size()-9);
	  cout << "on_barrier: " << on_barrier << endl;
	    
	}

      }
      }
    }

  // to get the correct order of actions
  sort(action_vector.begin(), action_vector.end(), [](const pair<string, int> &el1,
							const pair<string, int> &el2){
						       return el1.second<el2.second;
						     });

  for (auto el : action_vector){

    //example: (pick_from_barrier(yellow), 1)
    push_action(el.first, agent_i);
    //cout << el.first << "\t" << el.second << endl;
  }

}

void ActionManager::push_action(string action, int agent_i){

  /*
    pick_from_barrier(yellow)
    put_on_barrier(yellow)
    put(yellow,3,1)
    pick(yellow,3,1)
  */
  replace(action.begin(), action.end(), '(', ';');
  replace(action.begin(), action.end(), ',', ';');
  replace(action.begin(), action.end(), ')', ';');
  /*
    pick_from_barrier;yellow;
    put_on_barrier;yellow;
    put;yellow;3;1;
    pick;yellow;3;1;
  */
  action = action + to_string(agent_i);

  P->publish_action(action);
  action_robot_vector.push_back(action);
}

void ActionManager::write_initially(string agent, vector<string> &initially_vector){

  //cerr << classical_world_status_1.str() << endl;
  stringstream &classical_world_status = (agent == AGENT1) ? classical_world_status_1 : classical_world_status_2;
  classical_world_status.str("");
  
  for (auto el : initially_vector)
    classical_world_status << "initially " << el << ".\n";
}
