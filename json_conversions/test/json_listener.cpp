#include "ros/ros.h"

#include "json_conversions/json_conversions.hpp"

void callback(const nlohmann::json& data)
{
  ROS_INFO_STREAM("Received " << data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_listener");

  ros::NodeHandle nh;

  // nlohmann::json data = ros::topic::waitForMessage<nlohmann::json>("json");
  // ROS_INFO_STREAM("Received " << data);

  ros::Subscriber sub = nh.subscribe("json", 1, callback );
  ros::spin();

  return 0;
}
