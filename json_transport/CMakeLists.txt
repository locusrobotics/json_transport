cmake_minimum_required(VERSION 2.8.3)
project(json_transport)

set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++14;-Wall;-Werror")

find_package(catkin REQUIRED COMPONENTS json_msgs roscpp)

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS json_msgs roscpp
)
catkin_python_setup()

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY include/nlohmann/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

if(CATKIN_ENABLE_TESTING)
  find_package(roslint)
  roslint_cpp()
  roslint_python()

  catkin_install_python(
  PROGRAMS
    test/talker_py
    test/test_listener_py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

  add_executable(talker_cpp test/talker.cpp)
  target_link_libraries(talker_cpp ${catkin_LIBRARIES})

  catkin_add_executable_with_gtest(test_listener_cpp test/test_listener.cpp)
  target_link_libraries(test_listener_cpp ${catkin_LIBRARIES})

  find_package(rostest)
  add_rostest(test/transport.test ARGS talker_node:=talker_py)
  add_rostest(test/transport.test ARGS talker_node:=talker_cpp)

endif()
