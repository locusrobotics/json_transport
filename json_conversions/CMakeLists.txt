cmake_minimum_required(VERSION 2.8.3)
project(json_conversions)

set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++14;-Wall;-Werror")

find_package(catkin REQUIRED COMPONENTS json_msgs roscpp)

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS json_msgs roscpp
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY include/nlohmann/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

if(CATKIN_ENABLE_TESTING)

  add_executable(json_talker test/json_talker.cpp)
  target_link_libraries(json_talker ${catkin_LIBRARIES})

  add_executable(json_listener test/json_listener.cpp)
  target_link_libraries(json_listener ${catkin_LIBRARIES})

endif()
