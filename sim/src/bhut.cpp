#include "bhut.hpp"
#include "Eigen/src/Core/Matrix.h"
#include <limits>
#include <Eigen/Dense>

#include <iostream>

Body::Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel)
    :mass(m), p(pos), v(vel), a(accel)
{}

Body::Body()
    :mass(0), p(Eigen::Vector3d::Zero()), v(Eigen::Vector3d::Zero()), a(Eigen::Vector3d::Zero())
{}

bool Body::is_equal(const Body& other){
    return (mass == other.mass && p == other.p && v == other.v && a == other.a);
}

Node::Node(Eigen::Vector3d mini, Eigen::Vector3d maxi)
    :min(mini), max(maxi)
{}

Node::Node() :min{}, max{}, cm{}, children{} {
    for (int i = 0; i < 8; i++) {
        children[i] = nullptr;
    }
}

void Node::populate(const std::vector<Body> bodies) {
    if (bodies.size() == 1) {
        body = bodies[0];
        return;
    } else if (bodies.size() == 0) { return; }

    cm = Eigen::Vector3d::Zero();
    for (const Body& b : bodies) {
        cm += b.mass * b.p;
        mass += b.mass;
    }
    cm = cm / bodies.size();
    
    Eigen::Vector3d inc = (max-min)/2;
    for (int i = 0; i < 8; i++) {
        Eigen::Vector3d child_min(
            min[0] + (inc[0] * ((i & 1) == 1)),
            min[1] + (inc[1] * ((i & 2) == 2)),
            min[2] + (inc[2] * ((i & 4) == 4))
		);        
        children[i] = new Node(child_min, child_min + inc);

        std::vector<Body> child_bodies;
        for (const Body& b : bodies) {
            if (children[i]->vector_within(b.p)) {
                child_bodies.push_back(b);
            }
        }

        children[i]->populate(child_bodies);
    }
}

Eigen::Vector3d Body::compute_force(Eigen::Vector3d pos, float m){
    Eigen::Vector3d r = pos - p;
    double dist = r.norm();
    const double G = 6.67408e-11; //Change depending on what units we use
    double force = (G * mass * m) / (dist * dist);
    std::cout << force * r.normalized() << "\n";
    return force * r.normalized();
}

bool Node::vector_within(Eigen::Vector3d v) {
    return (v[0] >= min[0] && v[0] <= max[0] &&
            v[1] >= min[1] && v[1] <= max[1] &&
            v[2] >= min[2] && v[2] <= max[2]);
}

void Node::set_bounds(std::vector<Body> bodies){
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;

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

    max = Eigen::Vector3d(maxX, maxY, maxZ);
    min = Eigen::Vector3d(minX, minY, minZ);
}

Node Node::build_octree(const std::vector<Body> bodies){
    Node root = Node(Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero());
    root.set_bounds(bodies);
    root.populate(bodies); 
    return root;
}

void Node::set_subbounds(){ 
    Eigen::Vector3d inc = (max-min)/2;
    if(children[0] == NULL){
        children[0]->min = min;
        children[0]->max = min + inc;

        children[1]->min = Eigen::Vector3d(min[0] + inc[0], min[1], min[2]);
        children[1]->max = children[1]->min + inc;

        children[2]->min = Eigen::Vector3d(min[0], min[1] + inc[1], min[2]);
        children[2]->max = children[2]->min + inc;

        children[3]->min = Eigen::Vector3d(min[0] + inc[0], min[1] + inc[1], min[2]);
        children[3]->max = children[3]->min + inc;

        children[4]->min = Eigen::Vector3d(min[0], min[1], min[2] + inc[2]);
        children[4]->max = children[4]->min + inc;

        children[5]->min = Eigen::Vector3d(min[0] + inc[0], min[1], min[2] + inc[2]);
        children[5]->max = children[5]->min + inc;

        children[6]->min = Eigen::Vector3d(min[0], min[1] + inc[1], min[2] + inc[2]);
        children[6]->max = children[6]->min + inc;

        children[7]->min = Eigen::Vector3d(min[0] + inc[0], min[1] + inc[1], min[2] + inc[2]);
        children[7]->max = children[7]->min + inc;
    }
    else{
        for(int i = 0; i < 8; i++){
            children[i]->set_subbounds();
        }
    }
}

// std::array<Node, 8> Node::get_children() {
//     std::vector<Node> out{};
//     for (int i = 0; i < 8; i++) {
//         if (children[0] != NULL) {
//             out.push_back(*children[i]);
//         }
//     }
//     return out;
// }


Node Node::get_child(int i) {
    std::cout << children << " " << i << "\n";
    
	if (children[i] == nullptr ||
        body.p != Eigen::Vector3d::Zero() ||
        !is_sane_child(i)) {
		throw std::runtime_error("Whee");
	}
    std::cout << children[i] << "\n";
    std::cout << (long)&children[i] - (long)&children << "\n";
    std::cout << (long)children[i] - (long)&children << "\n";
    Node out = *children[i];
	return out;
}

bool Node::is_sane_child(int i) {
    return std::abs(((long)(&children[i]->cm) - (long)&children)) < 0x100000;
}

void Node::integrate_one_node(Body& cur, double theta, double dt){
    if (children[0] == NULL) {
        cur.a += cur.compute_force(body.p, body.mass) / cur.mass;
        cur.v += cur.a * dt;
        cur.p += cur.v * dt;
        return;
    }
    std::cout << "children: " << children << "\n\n\n";
    for(int i = 0; i < 8; i++){
        if (!is_sane_child(i)) continue;
        std::cout << "child: " << children[i] << "\n\n";
        double s = (max - min).norm();
        double d = (cur.p - children[i]->cm).norm();
        if(s < theta * d){
            children[i]->integrate_one_node(cur, theta, dt);
        }
        else{
            cur.a += cur.compute_force(children[i]->cm, children[i]->mass) / cur.mass;
            cur.v += cur.a * dt;
            cur.p += cur.v * dt;
        }
    }
}

void Node::integration_step(std::vector<Body>& bodies, double theta, double dt){
    for(Body& b : bodies){
        Eigen::Vector3d before = b.p;
        integrate_one_node(b, theta, dt);
        assert(b.p != before);
    }
}
