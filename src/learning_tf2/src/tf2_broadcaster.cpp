//Liam Mitchell 24/1/2018

#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>//for transforms
#include <tf2_ros/transform_broadcaster.h>//for publishing the transforms
#include <geometry_msgs/TransformStamped.h>//for timestamping?
#include <turtlesim/Pose.h>//for simulation

std::string turtle_name;//init turtle name object

void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf2_ros::TransformBroadcaster br;
	//creates a transform broadcaster to send
  geometry_msgs::TransformStamped transformStamped;
	//creates a transform object, gives appropriate data
  
  transformStamped.header.stamp = ros::Time::now();
	//timestamps with current time
  transformStamped.header.frame_id = "world";
	//set the name of the parent frame
  transformStamped.child_frame_id = turtle_name;
	//creates a sub-frame to hold the turtle
  transformStamped.transform.translation.x = msg->x;
	//translates message to x
  transformStamped.transform.translation.y = msg->y;
	//"" to y
  transformStamped.transform.translation.z = 0.0;
	//stuff with z
  tf2::Quaternion q;
  q.setRPY(0, 0, msg->theta);
	//sets roll, pitch, yaw
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();

  br.sendTransform(transformStamped);
	//sends the transform 
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster");

  ros::NodeHandle private_node("~");
  if (! private_node.hasParam("turtle"))
  {
    if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
    turtle_name = argv[1];
  }
  else
  {
    private_node.getParam("turtle", turtle_name);
  }
    
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);

  ros::spin();
  return 0;
};
