#pragma once 
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include "graph.h"
#include "sampler.h"

class MapGraphGenerator  {

private:
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    rclcpp::Node::SharedPtr m_nodePtr;
    Graph current_graph_;
    std::shared_ptr<nav_msgs::msg::OccupancyGrid> current_map_;
    rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub_;
    Sampler sampler_;

    bool getTf(const std::string& srcFrame, 
               const std::string& dstFrame, 
               geometry_msgs::msg::TransformStamped& outputTf);

    bool computeSampleScore(const std::pair<float,float>& sample, 
                            int32_t& score);

public:

    MapGraphGenerator(rclcpp::Node::SharedPtr node);

    ~MapGraphGenerator();

    void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);

    bool updateGraph();

};
