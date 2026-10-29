#ifndef RFID_POSE_ESTIMATOR_H_
#define RFID_POSE_ESTIMATOR_H_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <rfid_msgs/msg/tag.hpp>
#include <rfid_msgs/msg/tag_array.hpp>

class RfidPoseEstimator : public rclcpp::Node
{
public:

  RfidPoseEstimator();

private:

  void topic_callback(const std_msgs::msg::String::SharedPtr msg);

  void rfidAntennaCallback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);

  void rfidTagCallback(const rfid_msgs::msg::TagArray msg);

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr m_rfidAntennaSub;
  rclcpp::Subscription<rfid_msgs::msg::TagArray>::SharedPtr rfid_tag_sub_;
};


#endif  // RFID_POSE_ESTIMATOR_H_
