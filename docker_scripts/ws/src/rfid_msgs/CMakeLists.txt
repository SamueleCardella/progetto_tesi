cmake_minimum_required(VERSION 3.5)
project(rfid_msgs)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

# Generate messages
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Tag.msg"
  "msg/TagArray.msg"
  DEPENDENCIES std_msgs
)

# Install message files
install(
  DIRECTORY msg
  DESTINATION share/${PROJECT_NAME}
)

ament_package()