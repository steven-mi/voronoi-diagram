/**
 * This class is implements some utility functions on vectors
 */
#ifndef VORONOI_DIAGRAMME_VECTORUTILS_H
#define VORONOI_DIAGRAMME_VECTORUTILS_H

#include "vector"

class VectorUtils {
public:
    /**
     * This method generates a array with size size and a max value maxValue
     * @param size int
     * @param maxValue int
     * @return std::vector<int> with size size and values ranging from 0 to maxValue
     */
    static std::vector<int>
    generateRandomVector(int size, int maxValue);

    /**
     * This method generates a arrray with size (size1, size2) and a max value maxValue
     * @param size1 int
     * @param size2 int
     * @param maxValue int
     * @return std::vector<std::vector<int>> with size (size1, size2) and values ranging from 0 to maxValue
     */
    static std::vector<std::vector<int>>
    generateRandomVector2D(int size1, int size2, int maxValue);
};


#endif //VORONOI_DIAGRAMME_VECTORUTILS_H
