cmake_minimum_required(VERSION 3.24)
project(Incomplete_Relaxation_Method)

set(CMAKE_CXX_STANDARD 20)

add_executable(Incomplete_Relaxation_Method main.cpp Ready/IncRELAXMethod.cpp jdfs.cpp Ready/Power_method.cpp ff.cpp MethodOfRapidDescent.cpp)
