cmake_minimum_required(VERSION 3.5)
project(rfid_pose_estimator)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(rfid_msgs REQUIRED)

add_executable(rfid_pose_estimator
    src/rfid_pose_estimator.cpp
    src/main.cpp)
    
ament_target_dependencies(rfid_pose_estimator rclcpp std_msgs visualization_msgs rfid_msgs)

include_directories(
  include
)

install(TARGETS
  rfid_pose_estimator
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
