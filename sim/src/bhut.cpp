#include "bhut.hpp"

#include <Eigen/Dense>

Body::Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel)
    :mass(m), p(pos), v(vel), a(accel)
{}

Node::Node(Eigen::Vector3d mini, Eigen::Vector3d maxi)
    :min(mini), max(maxi)
{}

void Node::populate(const std::vector<Body> bodies) {
    Eigen::Vector3d inc = (max-min)/2;
    for (int i = 0; i < 3; i++) {
        for (int j : {-1, 1}) {
        }
    }
}

// Node Node::build_octree(const std::vector<Body> bodies) {
// }
