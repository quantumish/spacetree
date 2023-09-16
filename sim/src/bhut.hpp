#pragma once

#include <array>
#include <vector>

#include <Eigen/Dense>

class Body {
    float mass;
    Eigen::Vector3d p;
    Eigen::Vector3d v;
    Eigen::Vector3d a;

    Body();
    Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel);
    float compute_force(const Body& other); 
};

class Node {
    Body body;
    Eigen::Vector3d com;
    Eigen::Vector3d min; // bottom left
    Eigen::Vector3d max; // top right
    std::array<Node*, 8> children;

    Node(Eigen::Vector3d mini, Eigen::Vector3d maxi);
    void populate(const std::vector<Body> bodies);
    static Node build_octree(const std::vector<Body> bodies);
};

