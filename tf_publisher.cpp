#include "ros/ros.h"
#include <math.h>
#include <time.h>
#include "std_msgs/String.h"
//#include "first_project/Odom.h"
#include "nav_msgs/Odometry.h"
#include <tf/transform_broadcaster.h>
#include "second_project/Reset.h"
#include <sstream>

class odomNode{

private:
ros::NodeHandle n;
ros::Subscriber sub;
ros::Publisher pub;
ros::Publisher customPub;
tf::TransformBroadcaster br;
ros::ServiceServer resetter;

double L = 0.6;
double B = 0.4;
double x;
double y;
double z;
geometry_msgs::Quaternion th;
//ros::Time last_time;


public:
  odomNode(){
	//current_time = ros::Time::now();
        sub = n.subscribe("/t265/odom", 1000, &odomNode::subscriber, this);
        pub = n.advertise<nav_msgs::Odometry>("/tf_publisher", 1000);
        //customPub = n.advertise<first_project::Odom>("/custom_odometry", 1000);
        resetter = n.advertiseService("reset_odom", &odomNode::reset, this);

}

//Subscriber from bags

void subscriber(const nav_msgs::Odometry& msg){

	ros::Time current_time = ros::Time::now();

  x = msg.pose.pose.position.x;
  y =  msg.pose.pose.position.y;
  z = msg.pose.pose.position.z;
  th = msg.pose.pose.orientation;

  // Create a transform message
  geometry_msgs::TransformStamped transform;
  transform.header = msg.header;
  transform.child_frame_id = "base_footprint"; // Replace with your desired frame ID
  transform.transform.translation.x = x;
  transform.transform.translation.y = y;
  transform.transform.translation.z = z;
  transform.transform.rotation = th;

//  tf::Transform transform2;

//  tf2::fromMsg(transform, transform2);

// Extract position and orientation from the Odometry message
  geometry_msgs::Pose pose = msg.pose.pose;
  geometry_msgs::Point position = pose.position;
  geometry_msgs::Quaternion orientation = pose.orientation;

  // Create a tf::Vector3 for position and tf::Quaternion for orientation
  tf::Vector3 tf_position(position.x, position.y, position.z);
  tf::Quaternion tf_orientation(orientation.x, orientation.y, orientation.z, orientation.w);

  // Create a tf::Transform from the position and orientation
  tf::Transform transform2(tf_orientation, tf_position);

  // Broadcast the transform
  //static tf::TransformBroadcaster br;
  // Broadcast the transform
  br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "odom", "base_footprint"));

  ROS_INFO("tf published");


}
/*
void publishTf(nav_msgs::Odometry& msg){

  	ros::Time current_time = ros::Time::now();

    x = msg.pose.pose.position.x;
    y = msg.pose.pose.position.y;
    z = msg.pose.pose.position.z;
    th = msg.pose.pose.orientation;

  	transform.setOrigin( tf::Vector3(x, y, 0) );
	tf::Quaternion q;
	q.setRPY(0, 0, th);
	transform.setRotation(q);
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "t265", "base_footprint"));

	ROS_INFO("tf published");
}
*/
// Compute the reset

bool reset(second_project::Reset::Request &req, second_project::Reset::Response &res){
	x = 0.0;
	y = 0.0;
  z = 0.0;
	th.x= 0.0;
  th.y= 0.0;
  th.z= 0.0;
  th.w= 0.0;

	res.resetted =true;
	ROS_INFO("Odometry resetted");

	return true;
}

};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "tf_publisher");
	ROS_INFO("node started");

  odomNode odomNode;

  ros::spin();
	return 0;

}

