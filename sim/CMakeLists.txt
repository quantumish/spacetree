cmake_minimum_required(VERSION 3.20)

project(sim)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# find_package(MPI REQUIRED)

find_package(OpenMP)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# find_package(OpenCL REQUIRED)
# include_directories(${OpenCL_INCLUDE_DIRS})
# link_directories(${OpenCL_LIBRARY})

# find_package(TBB REQUIRED tbb)

add_executable(sim src/main.cpp src/bhut.cpp)
target_link_libraries(sim PUBLIC) # MPI::MPI_CXX
# if(OpenMP_CXX_FOUND)  
#   target_link_libraries(sim PUBLIC OpenMP::OpenMP_CXX)
#   # include_directories(OpenMP::OpenMP_INCLUDE_DIRS)
# endif()

find_package(pybind11 CONFIG REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")
pybind11_add_module(nbody_dev ./src/pybind.cpp ./src/bhut.cpp)
# target_link_libraries(nbody ${OpenCL_LIBRARY})
# target_link_libraries(sub_string_finder TBB::tbb)
