#include "bhut.hpp"
#include <Eigen/Dense>
#include <iostream>

std::vector<Body> naive_nbody(std::vector<Body> bodies, dt){
    for(Body b : bodies){
        for(Body other : bodies){
            if(b != other){
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
    vector<Body> bodies(10);
    for (int i = 0; i < 10; i++) {
        bodies[i] = Body(1, Eigen::Vector3d::Random(), Eigen::Vector3d::Random(), Eigen::Vector3d::Random());
    }
    Node root = Node::build_octree(bodies);

    Eigen::Vector3d a(1, 2, 3);
    std::cout << a << "\n";
    return 0;
}
