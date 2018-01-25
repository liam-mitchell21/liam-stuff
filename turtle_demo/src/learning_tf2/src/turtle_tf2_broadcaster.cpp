#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>//for transforms
#include <tf2_ros/transform_broadcaster.h>//for broadcasting
#include <geometry_msgs/TransformStamped.h>//for metadata
#include <turtlesim/Pose.h>//for position of turtle?

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg){
	//initializes poise stuff and msg (used for keyboard input)
  static tf2_ros::TransformBroadcaster br;
	//creates trandform broadcaster object br, used to send info l8r
  geometry_msgs::TransformStamped transformStamped;
  	//defines a transform object w/ metadata
  transformStamped.header.stamp = ros::Time::now();
	//timestamp
  transformStamped.header.frame_id = "world";
	//parent frame name (background)
  transformStamped.child_frame_id = turtle_name;
	//child frame name (operational thing)
  transformStamped.transform.translation.x = msg->x;
	//turns key press into move 
  transformStamped.transform.translation.y = msg->y;
	//"	"
  transformStamped.transform.translation.z = 0.0;
	//it's 2d boys
  tf2::Quaternion q;
	//define a fun quaternion obj for holding the transform (matrices?)
  q.setRPY(0, 0, msg->theta);
	//set q's roll pitch and yaw respectively (we only touch yaw here)
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();
	//send keys to quaternion object thing
  br.sendTransform(transformStamped);
	//send that shit out! let's hope there are listeners!
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster");
	//gotta do this b4 making a node

  ros::NodeHandle private_node("~");//not for PRYING EYES
  if (! private_node.hasParam("turtle"))
	//unsure what this is doing? some kinda check with the name
  {
    if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
    turtle_name = argv[1];
  }
  else
  {
    private_node.getParam("turtle", turtle_name);
  }

  ros::NodeHandle node;
	//all this bottom stuff is important I'm sure, figure out later
  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);

  ros::spin();
  return 0;
};
