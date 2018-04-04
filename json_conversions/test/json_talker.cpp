#include "ros/ros.h"

#include "json_conversions/json_conversions.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_talker");

  ros::NodeHandle nh;

  auto publisher = nh.advertise<nlohmann::json>("json", 1000, true);

  auto data = R"(
    {
      "hello this is json": 42
    }
  )"_json;

  ROS_INFO_STREAM("Publishing " << data << " sizeof " << sizeof(data));

  publisher.publish(data);

  ros::spin();

  return 0;
}
