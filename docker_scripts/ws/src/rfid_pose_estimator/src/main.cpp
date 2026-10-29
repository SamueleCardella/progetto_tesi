#include "rfid_pose_estimator/rfid_pose_estimator.h"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RfidPoseEstimator>());
  rclcpp::shutdown();
  return 0;
}