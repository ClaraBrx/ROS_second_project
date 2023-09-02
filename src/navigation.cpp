#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <fstream>
#include <sstream>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "goal_publisher1");

  ros::NodeHandle n;

  std::string file_path = "vuoto";

  const std::string PARAM_NAME = "~/csv_file_path";
  ros::param::get(PARAM_NAME, file_path);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(10.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // Read the goal points from the CSV file
  std::ifstream csvFile(file_path);
  std::string line;

  while (std::getline(csvFile, line)) {
    std::istringstream iss(line);
    std::string x, y, o_z, o_w;
    if (!(std::getline(iss, x, ',') && std::getline(iss, y, ',') && std::getline(iss, o_z, ','))){
      continue; // Skip invalid lines
    }

    // If there are only 3 values, set o_w to 0
    if (!std::getline(iss, o_w, ',')) {
      o_w = "1";
    }

    // Parse the goal point values
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = std::stod(x);
    goal.target_pose.pose.position.y = std::stod(y);
    goal.target_pose.pose.orientation.z = std::stod(o_z);
    goal.target_pose.pose.orientation.w = 1.0;

    // Send the goal point
    ac.sendGoal(goal);
    ac.waitForResult();

    // Check the result and print success or failure message
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved to the goal point");
    else
      ROS_INFO("The base failed to reach the goal point for some reason");
  }

  return 0;
}
