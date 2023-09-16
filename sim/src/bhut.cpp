#include "bhut.hpp"

#include <Eigen/Dense>

Body::Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel)
    :mass(m), p(pos), v(vel), a(accel)
{}

Body::Body()
    :mass(0), p(0), v(0), a(0)
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

Eigen::Vector3d Body::compute_force(const Body& other){
    Eigen::Vector3d r = other.p - p;
    double dist = r.norm();
    double G = 6.67408e-11; //Change depending on what units we use
    double force = G * mass * other.mass / (dist * dist);
    return force * r.normalized();
}
