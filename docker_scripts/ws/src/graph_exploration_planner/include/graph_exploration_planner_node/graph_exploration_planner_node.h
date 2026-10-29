#ifndef RFID_TAG_MAPPING_NODE_H_
#define RFID_TAG_MAPPING_NODE_H_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include "graph_exploration_planner_node/map_graph_generator.h"

class GraphExplorationPlannerNode : public rclcpp::Node
{
public:

  GraphExplorationPlannerNode();

  void initialize();

private:

  void topic_callback(const std_msgs::msg::String::SharedPtr msg);

  void rfidAntennaCallback(const visualization_msgs::msg::MarkerArray::SharedPtr msg);

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::Subscription<visualization_msgs::msg::MarkerArray>::SharedPtr m_rfidAntennaSub;
  std::shared_ptr<MapGraphGenerator> m_mapGraphGenerator;
};


#endif  // RFID_TAG_MAPPING_NODE_H_
