#include "ros/ros.h"

#include "json_transport/json_transport.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "json_talker");

  ros::NodeHandle nh;

  auto publisher = nh.advertise<nlohmann::json>("json", 1000, true);

  auto data = R"(
    {
      "hello_this_is_json": 42
    }
  )"_json;

  ROS_INFO_STREAM("Publishing " << data);

  publisher.publish(data);

  ros::spin();

  return 0;
}
