project(tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(VORONOI_PATH ${PROJECT_SOURCE_DIR}/../src)
include_directories(${VORONOI_PATH})

option(USE_OPENACC "Use OpenACC instead of OpenMP" OFF) #ON by default
if (USE_OPENACC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lcublas -fopenacc -fopt-info-optimized-omp -fno-stack-protector -lm -foffload=-lm -fno-fast-math -fno-associative-math")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
endif (USE_OPENACC)
unset(USE_OPENACC CACHE)

add_executable(Google_Tests_run VoronoiGeneratorTest.cpp ${VORONOI_PATH}/generator/VoronoiGenerator.cpp ${VORONOI_PATH}/generator/VoronoiGenerator.h ${VORONOI_PATH}/utils/VectorUtils.cpp ${VORONOI_PATH}/utils/VectorUtils.h)
target_link_libraries(Google_Tests_run gtest gtest_main)

