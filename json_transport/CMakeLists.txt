cmake_minimum_required(VERSION 3.5)
project(json_transport)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Werror -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(json_msgs REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(${PROJECT_NAME} INTERFACE)

install(TARGETS ${PROJECT_NAME}
  EXPORT "export_${PROJECT_NAME}"
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
  INCLUDES DESTINATION include
)

install(
  DIRECTORY
    include/${PROJECT_NAME}/
  DESTINATION
    include/${PROJECT_NAME}
)

#########
# Python
#########

find_package(ament_cmake_python REQUIRED)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

install(
  FILES requirements.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}
)

#if(CATKIN_ENABLE_TESTING)
#  find_package(catkin_virtualenv)
#  find_package(roslint)
#
#  # Python configuration
#  find_package(ament_cmake_virtualenv)
#  ament_generate_virtualenv(
#    PYTHON_VERSION 3.12
#    INPUT_REQUIREMENTS requirements.in
#  )
#
#  ament_python_install_package(
#      locus_ota_service
#  )
#
#
#  catkin_generate_virtualenv(
#    INPUT_REQUIREMENTS requirements.in
#  )
#
#  roslint_cpp()
#  roslint_python()
#
#  catkin_install_python(
#  PROGRAMS
#    test/talker_py
#    test/test_listener_py
#    test/test_packed_json.py
#  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
#
#  add_executable(talker_cpp test/talker.cpp)
#  target_link_libraries(talker_cpp PUBLIC
#    rclcpp::rclcpp
#    json_msgs
#  )
#
#  catkin_add_executable_with_gtest(test_listener_cpp test/test_listener.cpp)
#  target_link_libraries(test_listener_cpp ${catkin_LIBRARIES})
#
#  find_package(rostest)
#  add_rostest(test/transport.test ARGS talker_node:=talker_py)
#  add_rostest(test/transport.test ARGS talker_node:=talker_cpp)
#  catkin_add_nosetests(test/test_packed_json.py)
#
#endif()

ament_export_targets("export_${PROJECT_NAME}")
ament_package()
