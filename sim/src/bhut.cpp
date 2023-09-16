#include "bhut.hpp"
#include <limits>
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

bool Node::vector_within(Eigen::Vector3d v) {
    return (v[0] >= min[0] && v[0] <= max[0] &&
            v[1] >= min[1] && v[1] <= max[1] &&
            v[2] >= min[2] && v[2] <= max[2]);
}

Eigen::Vector3d get_min(std::vector<Body> bodies){
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    for(Body b : bodies){
        if(b.p[0] < minX){
            minX = b.p[0];
        }
        if(b.p[1] < minY){
            minY = b.p[1];
        }
        if(b.p[2] < minZ){
            minZ = b.p[2];
        }
    }

    return Eigen::Vector3d(minX, minY, minZ);
}

Eigen::Vector3d get_max(std::vector<Body> bodies){
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;

    for(Body b : bodies){
        if(b.p[0] > maxX){
            maxX = b.p[0];
        }
        if(b.p[1] > maxY){
            maxY = b.p[1];
        }
        if(b.p[2] > maxZ){
            maxZ = b.p[2];
        }
    }

    return Eigen::Vector3d(maxX, maxY, maxZ);
}