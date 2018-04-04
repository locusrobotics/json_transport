#include "ros/ros.h"

#include "json_transport/json_transport.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_listener");

  ros::NodeHandle nh;

  boost::shared_ptr<const nlohmann::json> data = ros::topic::waitForMessage<nlohmann::json>("json");
  ROS_INFO_STREAM("Received single " << *data);

  return 0;
}
