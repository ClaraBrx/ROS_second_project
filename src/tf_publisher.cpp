#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class TFPublisher
{
public:
  TFPublisher()
  {
    // Initialize ROS node handle
    nh = ros::NodeHandle();

    // Subscribe to the odometry topic
    odom_sub = nh.subscribe("/t265/odom", 10, &TFPublisher::odomCallback, this);
    //scan_sub = nh.subscribe("/scan", 10, &TFPublisher::scanCallback, this);
    
    //odom_pub = nh.advertise<nav_msgs::Odometry>("/base_footprint", 10);
  }

private:
  ros::NodeHandle nh;
  tf::TransformBroadcaster tf_broadcaster;
  ros::Subscriber odom_sub;
  ros::Publisher odom_pub;

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
  {
    // Convert the odometry message to a tf transform
    geometry_msgs::TransformStamped odom_transform;
    odom_transform.header.stamp = msg->header.stamp;
    odom_transform.header.frame_id = "t265";
    odom_transform.child_frame_id = "base_footprint";

    odom_transform.transform.translation.x = msg->pose.pose.position.x;
    odom_transform.transform.translation.y = msg->pose.pose.position.y;
    odom_transform.transform.translation.z = msg->pose.pose.position.z;

    odom_transform.transform.rotation = msg->pose.pose.orientation;

    // Publish the tf transform
    tf_broadcaster.sendTransform(odom_transform);
    
    
/*
    // Publish the odometry data as well
    nav_msgs::Odometry odom;
    odom.header = msg->header;
    odom.child_frame_id = "base_link";
    odom.pose = msg->pose;
    odom.twist = msg->twist;

    odom_pub.publish(odom);
    */
  }
  /*
  void scanCallback(const sensor_msgs::LaserScan& msg)
  {
    // Convert the scan message
    geometry_msgs::TransformStamped odom_transform;
    odom_transform.header.stamp = msg->header.stamp;
    odom_transform.header.frame_id = "t265";
    odom_transform.child_frame_id = "base_link";

    odom_transform.transform.translation.x = msg->pose.pose.position.x;
    odom_transform.transform.translation.y = msg->pose.pose.position.y;
    odom_transform.transform.translation.z = msg->pose.pose.position.z;

    odom_transform.transform.rotation = msg->pose.pose.orientation;

    // Publish the tf transform
    tf_broadcaster.sendTransform(odom_transform);
    }

*/
};
int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf_publisher");
  TFPublisher tf_publisher;
  ros::spin();
  return 0;
}

