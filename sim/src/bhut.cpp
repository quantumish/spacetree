#include <array>
#include <Eigen/Dense>

Body::Body(){
    mass = 0;
    p = Eigen::Vector3d(0, 0, 0);
    v = Eigen::Vector3d(0, 0, 0);
    a = Eigen::Vector3d(0, 0, 0);
}

Body::Body(float m, Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d accel){
    mass = m;
    p = pos;
    v = vel;
    a = accel;
}

Eigen::Vector3d Body::ComputeForce(Body other){
    Eigen::Vector3d r = other.p - p;
    double dist = r.norm();
    double force = G * mass * other.mass / (dist * dist);
    return force * r.normalized();
}