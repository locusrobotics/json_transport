#include "ros/ros.h"

#include "json_transport/json_transport.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_talker");

  ros::NodeHandle nh;

  auto publisher = nh.advertise<nlohmann::json>("json", 1000, true);

  std::string data_string;
  nh.getParam("test_data", data_string);
  auto data = nlohmann::json::parse(data_string);

  ROS_INFO_STREAM("Publishing " << data);

  publisher.publish(data);

  ros::spin();

  return 0;
}
