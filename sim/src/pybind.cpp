#include "bhut.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/eigen.h>

namespace py = pybind11;

PYBIND11_MODULE(nbody_dev, m) {
	m.doc() = "Debugging utilities for nbody.";
	py::class_<Body>(m, "Body")
        .def(py::init<>())
		.def(py::init<float, Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d>())
		.def_readonly("mass", &Body::mass)
		.def_readonly("position", &Body::p)
		.def_readonly("velocity", &Body::v)
		.def_readonly("acceleration", &Body::a);
	py::class_<Node>(m, "Node")
        .def(py::init<Eigen::Vector3d, Eigen::Vector3d>())
        .def(py::init<>())
		.def_readonly("min", &Node::min)
		.def_readonly("max", &Node::max)
        .def("get_child", &Node::get_child)
		.def_readonly("cm", &Node::cm)
		.def_readonly("body", &Node::body)
        .def("integration_step", &Node::integration_step)
		.def_static("build_octree", &Node::build_octree);
}

