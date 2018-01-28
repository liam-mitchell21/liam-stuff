#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>//important for recieving info
#include <geometry_msgs/TransformStamped.h>//for metadata on transforms
#include <geometry_msgs/Twist.h>//coordinate messages!
#include <turtlesim/Spawn.h>//to spawn the 'listener' turtle

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_listener");

  ros::NodeHandle node;
	//below lies some turtle sim specificities
  ros::service::waitForService("spawn");
  ros::ServiceClient spawner =
    node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn turtle;
  turtle.request.x = 4;
  turtle.request.y = 2;
  turtle.request.theta = 0;
  turtle.request.name = "turtle2";
  spawner.call(turtle);

  ros::Publisher turtle_vel =
    node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);
	//create tflistener object, with a 10sec buffer to prevent overload
  ros::Rate rate(10.0);
  while (node.ok()){
    geometry_msgs::TransformStamped transformStamped;
    try{
      ros::Time now = ros::Time::now();
      ros::Time past = now - ros::Duration(5.0);
      transformStamped = tfBuffer.lookupTransform("turtle2", now, 
			       "carrot1", past,
			       "world", ros::Duration(1.0));
	//want to transform source frame into target frame
	//time 0 gets most recent
    }
    catch (tf2::TransformException &ex) {//if it fails to transform
      ROS_WARN("%s",ex.what());//ignore & get listener to keep on keeping on
      ros::Duration(1.0).sleep();
      continue;
    }
	//oh shit that's math down there!
    geometry_msgs::Twist vel_msg;

    vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y,
                                    transformStamped.transform.translation.x);
    vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) +
                                  pow(transformStamped.transform.translation.y, 2));
    turtle_vel.publish(vel_msg);

    rate.sleep();
  }
  return 0;
};
