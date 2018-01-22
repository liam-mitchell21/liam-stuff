//Liam Mitchell 22/1/2018

//Based on the ros navigation tutorial 
  //@ http://wiki.ros.org/navigation/Tutorials/RobotSetup/TF

#include <ros/ros.h>
#include <tf/transform_broadcaster.h> //helps publish our transforms

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  ros::Rate r(100);

  tf::TransformBroadcaster broadcaster; 
    //creates a transform broadcaster object

  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),
          //passes the transform, rotational with quat(pitch, roll, yaw, ?)
          //vector3 is translation offset in meters (x, y, z)
        ros::Time::now(),"parent_node", "child_node"));
          //gives transform a timestamp
          //name of parent and child node respectively
    r.sleep();
  }
}
