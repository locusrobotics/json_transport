cmake_minimum_required(VERSION 3.8)
project(json_transport)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(json_msgs REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(include)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

ament_python_install_package(${PROJECT_NAME} PACKAGE_DIR src/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_virtualenv REQUIRED)
  find_package(ament_cmake_pytest REQUIRED)
  find_package(launch_testing_ament_cmake REQUIRED)

  ament_generate_virtualenv(
    PYTHON_VERSION 3
  )

  install(FILES requirements.txt
    DESTINATION share/${PROJECT_NAME}
  )

  install(PROGRAMS
    test/talker_py
    test/test_listener_py
    DESTINATION lib/${PROJECT_NAME}
  )

  add_executable(talker_cpp test/talker.cpp)
  ament_target_dependencies(talker_cpp json_msgs rclcpp)
  target_link_libraries(talker_cpp nlohmann_json::nlohmann_json)

  add_executable(test_listener_cpp test/test_listener.cpp)
  ament_target_dependencies(test_listener_cpp json_msgs rclcpp)
  target_link_libraries(test_listener_cpp nlohmann_json::nlohmann_json)

  install(TARGETS
    talker_cpp
    test_listener_cpp
    DESTINATION lib/${PROJECT_NAME}
  )

  ament_add_pytest_test(test_packed_json test/test_packed_json.py)
  add_launch_test(test/transport_py_talker.launch.py TIMEOUT 20)
  add_launch_test(test/transport_cpp_talker.launch.py TIMEOUT 20)
endif()

ament_export_include_directories(include)
ament_export_dependencies(json_msgs rclcpp)

ament_package()
