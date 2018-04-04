#include "ros/ros.h"

#include "json_conversions/json_conversions.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_listener");

  ros::NodeHandle nh;

  auto data = ros::topic::waitForMessage<nlohmann::json>("json");

  ROS_INFO_STREAM("Received " << data << " sizeof " << sizeof(data));

  return 0;
}
