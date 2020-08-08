#include <random>
#include <algorithm>
#include "VectorUtils.h"


std::vector<int> VectorUtils::generateRandomVector(int size, int maxValue) {
    std::vector<int> v(size);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist{0, maxValue};

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::generate(v.begin(), v.end(), gen);
    return v;
}

std::vector<std::vector<int>> VectorUtils::generateRandomVector2D(int height, int width, int maxValue) {
    std::vector<std::vector<int>> vec2D = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));

    for (int i = 0; i < vec2D.size(); i++) {
        vec2D[i] = generateRandomVector(width, maxValue);
    }
    return vec2D;
}






