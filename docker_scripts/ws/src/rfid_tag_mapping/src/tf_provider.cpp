#pragma once 
#include "rfid_tag_mapping_node/tf_provider.h"

TfProvider::TfProvider(rclcpp::Node::SharedPtr node) : tf_buffer_(node->get_clock()), tf_listener_(tf_buffer_), m_nodePtr(node) {

}

TfProvider::~TfProvider() {

}
