cmake_minimum_required(VERSION 3.10)

project(voronoi_diagram)
add_subdirectory(tests)

option(USE_OPENACC "Use OpenACC instead of OpenMP" OFF) #ON by default
if(USE_OPENACC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lcublas -fopenacc -fopt-info-optimized-omp -fno-stack-protector -lm -foffload=-lm -fno-fast-math -fno-associative-math")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
endif(USE_OPENACC)
unset(USE_OPENACC CACHE)


add_executable(voronoi_diagram src/main.cpp src/generator/VoronoiGenerator.cpp src/generator/VoronoiGenerator.h src/utils/FileReader.cpp src/utils/FileReader.h src/utils/VectorUtils.cpp src/utils/VectorUtils.h)
