#pragma once 
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

class TfProvider  {

private:
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    rclcpp::Node::SharedPtr m_nodePtr;

public:

    TfProvider(rclcpp::Node::SharedPtr node);

    ~TfProvider();

    geometry_msgs::msg::TransformStamped getTf(const std::string& srcFrame, 
                                               const std::string& dstFrame);

};
