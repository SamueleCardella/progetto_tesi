#include "rfid_pose_estimator/rfid_pose_estimator.h"


RfidPoseEstimator::RfidPoseEstimator() : Node("rfid_pose_estimator") {
  // Publisher
  publisher_ = this->create_publisher<std_msgs::msg::String>("output_topic", 10);

  // Subscriber
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "input_topic", 10,
    std::bind(&RfidPoseEstimator::topic_callback, this, std::placeholders::_1)
  );
  m_rfidAntennaSub = this->create_subscription<visualization_msgs::msg::MarkerArray>(
    "rfid/tag_position", 10,
    std::bind(&RfidPoseEstimator::rfidAntennaCallback, this, std::placeholders::_1)
  );
  rfid_tag_sub_ = this->create_subscription<rfid_msgs::msg::TagArray>(
    "rfid/tag_array", 10,
    std::bind(&RfidPoseEstimator::rfidTagCallback, this, std::placeholders::_1)
  );
}

void RfidPoseEstimator::topic_callback(const std_msgs::msg::String::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());

  // Processing data
  auto message = std_msgs::msg::String();
  message.data = "Processed: " + msg->data;

  // Publishing the processed data
  publisher_->publish(message);
}

void RfidPoseEstimator::rfidAntennaCallback(const visualization_msgs::msg::MarkerArray::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received: ");
}

void RfidPoseEstimator::rfidTagCallback(const rfid_msgs::msg::TagArray msg) {
  RCLCPP_INFO(this->get_logger(), "Received rfid tag: ");
}


