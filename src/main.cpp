#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

ros::Subscriber gamepadDataSub;
ros::Publisher cmdVelPub;

void SubGamepadData(const sensor_msgs::Joy& msg) {
  geometry_msgs::Twist cmdVel;
  cmdVel.linear.x = msg.axes[1];
  cmdVel.linear.y = msg.axes[0];
  cmdVel.angular.x = -msg.axes[3];
  cmdVel.angular.y = msg.axes[4];
  cmdVelPub.publish(cmdVel);
}

int main(int argc, char** argv) {
  ROS_INFO("start quadruped_ctrl node");

  ros::init(argc, argv, "gamepad_ctrl");
  ros::NodeHandle n;
  ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                 ros::console::levels::Info);

  gamepadDataSub = n.subscribe("/joy", 10, &SubGamepadData);
  cmdVelPub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  ros::spin();
  return 0;
}