#pragma once

#include <array>
#include <vector>

#include <Eigen/Dense>

struct Body {
    float mass;
    float angular_momentum;
    float radius;
    Eigen::Vector3d p;
    Eigen::Vector3d v;
    Eigen::Vector3d a;

    bool is_equal(const Body& other);
    
    Body();
    Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel);
    Eigen::Vector3d compute_force(Eigen::Vector3d pos, float m); 
};

struct Node {
    Body body;
    float mass;
    Eigen::Vector3d cm;
    Eigen::Vector3d min; // bottom left
    Eigen::Vector3d max; // top right
    Node* children[8];

    Node();
    
    Node get_child(int i);    

    bool is_sane_child(int i);
    
    bool vector_within(Eigen::Vector3d v);
    void set_bounds(std::vector<Body> bodies); //Useful for initial node only
    void set_subbounds();

    void integrate_one_node(Body& b, double theta, double dt);
    void integration_step(std::vector<Body>& bodies, double theta, double dt);

    Node(Eigen::Vector3d mini, Eigen::Vector3d maxi);
    void populate(const std::vector<Body> bodies);
    static Node build_octree(const std::vector<Body> bodies);
};

