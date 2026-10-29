#include "graph_exploration_planner_node/graph_exploration_planner_node.h"


GraphExplorationPlannerNode::GraphExplorationPlannerNode() : Node("graph_exploration_planner_node") {

	// Publisher
	publisher_ = this->create_publisher<std_msgs::msg::String>("output_topic", 10);

	// Subscriber
	subscription_ = this->create_subscription<std_msgs::msg::String>(
					"input_topic", 10,
					std::bind(&GraphExplorationPlannerNode::topic_callback, this, std::placeholders::_1));

	m_rfidAntennaSub = this->create_subscription<visualization_msgs::msg::MarkerArray>(
					   "rfid/tag_position", 10,
					   std::bind(&GraphExplorationPlannerNode::rfidAntennaCallback, this, std::placeholders::_1));
}

void GraphExplorationPlannerNode::initialize() {
	m_mapGraphGenerator = std::make_shared<MapGraphGenerator>(shared_from_this());
}

void GraphExplorationPlannerNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {
	RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());

	// Processing data
	auto message = std_msgs::msg::String();
	message.data = "Processed: " + msg->data;

	// Publishing the processed data
	publisher_->publish(message);
}

void GraphExplorationPlannerNode::rfidAntennaCallback(const visualization_msgs::msg::MarkerArray::SharedPtr msg) {
	// RCLCPP_INFO(this->get_logger(), "Received: ");
}


