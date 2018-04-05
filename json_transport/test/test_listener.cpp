#include "gtest/gtest.h"
#include "ros/ros.h"

#include "json_transport/json_transport.hpp"

TEST(TestSuite, listen_test)
{
  ros::NodeHandle nh;

  std::string data_string;
  nh.getParam("test_data", data_string);
  auto data = nlohmann::json::parse(data_string);

  boost::shared_ptr<const nlohmann::json> received = ros::topic::waitForMessage<nlohmann::json>("json");
  ROS_INFO_STREAM("Received " << *received);

  EXPECT_EQ(data, *received);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "json_listener");
  return RUN_ALL_TESTS();
}
