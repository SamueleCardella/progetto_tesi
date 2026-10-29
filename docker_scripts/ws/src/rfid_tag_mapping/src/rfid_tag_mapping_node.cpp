#include "rfid_tag_mapping_node/rfid_tag_mapping_node.h"


RfidTagMappingNode::RfidTagMappingNode() : Node("rfid_tag_mapping_node") {

	m_tfProvider = std::make_shared<TfProvider>(shared_from_this());
	// Publisher
	publisher_ = this->create_publisher<std_msgs::msg::String>("output_topic", 10);

	// Subscriber
	subscription_ = this->create_subscription<std_msgs::msg::String>(
					"input_topic", 10,
					std::bind(&RfidTagMappingNode::topic_callback, this, std::placeholders::_1));

	m_rfidAntennaSub = this->create_subscription<visualization_msgs::msg::MarkerArray>(
					   "rfid/tag_position", 10,
					   std::bind(&RfidTagMappingNode::rfidAntennaCallback, this, std::placeholders::_1));
}

void RfidTagMappingNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {
	RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());

	// Processing data
	auto message = std_msgs::msg::String();
	message.data = "Processed: " + msg->data;

	// Publishing the processed data
	publisher_->publish(message);
}

void RfidTagMappingNode::rfidAntennaCallback(const visualization_msgs::msg::MarkerArray::SharedPtr msg) {
	RCLCPP_INFO(this->get_logger(), "Received: ");
}


