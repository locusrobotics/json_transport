cmake_minimum_required(VERSION 3.5)
project(json_msgs)

set(CMAKE_CXX_STANDARD 17)

find_package(ament_cmake)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Json.msg"
  DEPENDENCIES
  ADD_LINTER_TESTS
)
