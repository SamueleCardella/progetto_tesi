#include "rfid_tag_mapping_node/rfid_tag_mapping_node.h"

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RfidTagMappingNode>());
  rclcpp::shutdown();
  return 0;
}