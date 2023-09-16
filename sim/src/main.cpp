#include "bhut.hpp"
#include "bhut.cpp"
#include <Eigen/Dense>
#include <iostream>

std::vector<Body> naive_nbody(std::vector<Body> bodies, double dt){
    for(Body b : bodies){
        for(Body other : bodies){
            if(!b.is_equal(other)){
                b.a += b.compute_force(other) / b.mass;
            }
        }
    }
    for(Body b : bodies){
        b.v += b.a * dt;
        b.p += b.v * dt;
    }
    return bodies;
}

int main() {
    std::vector<Body> bodies(10);
    for (int i = 0; i < 10; i++) {
        bodies[i] = Body(1, Eigen::Vector3d::Random(), Eigen::Vector3d::Random(), Eigen::Vector3d::Random());
    }
    Node root = Node::build_octree(bodies);
    std::vector<Body> bodies2 = naive_nbody(bodies, 1);
    std::cout << bodies2[0].p << "\n";
    root.integration_step(bodies, 1.5, 1);
    std::cout << bodies[0].p << "\n";
    
    return 0;
}
