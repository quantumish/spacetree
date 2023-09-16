#include <array>
#include <Eigen/Dense>

class Body {
    float mass;
    Eigen::Vector3d p;
    Eigen::Vector3d v;
    Eigen::Vector3d a;

    Body();
    Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel);
    ComputeForce(Body other);
};

class Node {
    Body body;
    Eigen::Vector3d com;
    std::array<Node*, 8> children;

    Node();
};

