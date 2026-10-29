#pragma once 
#include "graph_exploration_planner_node/map_graph_generator.h"

#define LOCAL_EXPLORATION_X_SIZE 1.0
#define LOCAL_EXPLORATION_Y_SIZE 1.0

MapGraphGenerator::MapGraphGenerator(rclcpp::Node::SharedPtr node) : tf_buffer_(node->get_clock()), tf_listener_(tf_buffer_), m_nodePtr(node) {

map_sub_ = m_nodePtr->create_subscription<nav_msgs::msg::OccupancyGrid>(
					"map", 10,
					std::bind(&MapGraphGenerator::mapCallback, this, std::placeholders::_1));

}

MapGraphGenerator::~MapGraphGenerator() {

}

void MapGraphGenerator::mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
    current_map_ = msg;
    updateGraph();
}

bool MapGraphGenerator::updateGraph() {
    bool retVal = false;
    if(current_map_ != nullptr) {
        geometry_msgs::msg::TransformStamped currentTf; 
        if(getTf("map","base_link", currentTf)) {
            std::vector<std::pair<float,float>> samples = 
                        sampler_.sampleArea(currentTf.transform.translation.x - LOCAL_EXPLORATION_X_SIZE, 
                                            currentTf.transform.translation.x + LOCAL_EXPLORATION_X_SIZE,
                                            currentTf.transform.translation.y - LOCAL_EXPLORATION_Y_SIZE,
                                            currentTf.transform.translation.y + LOCAL_EXPLORATION_Y_SIZE, 
                                            20);
            for(size_t i = 0; i < samples.size(); i++) {
                int32_t sampleScore = 0;
                std::cout << "iteration number " << i << std::endl;
                if(computeSampleScore(samples[i], sampleScore)) {
                    if(sampleScore < 0) {
                        std::cout << "SAMPLE FOUD" << std::endl;
                    }
                }
            }
        }
    }
    return retVal;
}

bool MapGraphGenerator::getTf(const std::string& srcFrame, 
                              const std::string& dstFrame, 
                              geometry_msgs::msg::TransformStamped& outputTf) {
    bool retVal = false;
    try {
        outputTf = tf_buffer_.lookupTransform(dstFrame, srcFrame, tf2::TimePointZero);
        retVal = true;
    } catch (tf2::TransformException &ex) {
        RCLCPP_ERROR(m_nodePtr->get_logger(), "Could not transform %s to %s: %s", srcFrame.c_str(), dstFrame.c_str(), ex.what());
    }
    return retVal;
}

bool MapGraphGenerator::computeSampleScore(const std::pair<float,float>& sample, 
                                           int32_t& score) {
    bool retVal = false;
    if(current_map_ != nullptr) {

        float map_x = (sample.first - current_map_->info.origin.position.x) / current_map_->info.resolution;
        float map_y = (sample.second - current_map_->info.origin.position.y) / current_map_->info.resolution;

        int map_idx_x = static_cast<int>(map_x);
        int map_idx_y = static_cast<int>(map_y);

        for(size_t i = map_idx_x - 2; i <= map_idx_x + 2; i++) {
            for(size_t j = map_idx_y - 2; i <= map_idx_y + 2; j++) {
                int index = j * current_map_->info.width + i;
                if (index >= 0 && index < static_cast<int>(current_map_->data.size())) {
                    score += current_map_->data[index];
                }
                else {
                    continue;
                }
            }
        }
        retVal = false;
    }
    return retVal;
}