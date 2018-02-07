#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

void callback(const std_msgs::String)
{
  ROS_INFO("callback");
}

int main(int argc, char** argv){
  ros::init(argc, argv, "pixie_tf2_listener");

  ros::NodeHandle node;

  //ros::Publisher pixie_pub = node.advertize<geometry_msgs::Twist>("name?",10);

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  ros::Rate rate(100);

  while (node.ok())
  {

  ros::Subscriber sub node.subscribe("name",1000,callback)

  ros::spinOnce();
  r.sleep();
  }
  return 0;
};