#pragma once 

#include <geometry_msgs/msg/pose.hpp>

struct node {
    geometry_msgs::msg::Pose pose;
    uint8_t type;
    int32_t exploration_ratio;
};

enum NodeType : uint8_t {
    PARENT = 0,
    CHILD = 1
};


class Graph {
private:


public:
    std::vector<node> graph_;

    Graph(){ 

    }

    Graph(const Graph& graph){
        graph_ = graph.graph_;
    }

    ~Graph(){
        
    }
};

