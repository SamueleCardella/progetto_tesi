#include "graph_exploration_planner_node/graph_exploration_planner_node.h"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<GraphExplorationPlannerNode>();
  node->initialize();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}