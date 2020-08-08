/**
 * This class is implements Voronoi Diagrams with different frameworks
 */
#ifndef VORONOI_DIAGRAMME_VORONOIGENERATOR_H
#define VORONOI_DIAGRAMME_VORONOIGENERATOR_H


#include <vector>

class VoronoiGenerator {
public:
    /**
     * This method returns the voronoi diagram of given points in a 1-dimensional array with size
     * height * width. The points are defined as two vectors. This implementation is sequential,
     * thus it may be slow.
     *
     * @param height int
     * @param width int
     * @param xVec int array: x coordinates of the points
     * @param yVec int array: y coordinates of the points
     * @param vecSize int: size of the vectors xVec and yVec
     * @return int array with values ranging from 0 to vecSize and size height * width.
     *         Each value correspond to a voronoi region e.g. [0, 0, 1] means that
     *         the first two values are in the region of point 0 and the last value
     *         is in the region of point 1.     */
    static int *
    generateVoronoiDiagram(int height, int width, int *xVec, int *yVec, int vecSize);


    /**
     * This method returns the voronoi diagram of given points in a 1-dimensional array with size
     * height * width. The points are defined as two vectors. This implementation with OpenMP. Make sure
     * that the files are compiled correctly
     *
     * @param height int
     * @param width int
     * @param xVec int array: x coordinates of the points
     * @param yVec int array: y coordinates of the points
     * @param vecSize int: size of the vectors xVec and yVec
     * @return int array with values ranging from 0 to vecSize and size height * width.
     *         Each value correspond to a voronoi region e.g. [0, 0, 1] means that
     *         the first two values are in the region of point 0 and the last value
     *         is in the region of point 1.
     */
    static int *
    generateVoronoiDiagramOMP(int height, int width, int *xVec, int *yVec, int vecSize);

    /**
     * This method returns the voronoi diagram of given points in a 1-dimensional array with size
     * height * width. The points are defined as two vectors. This implementation with OpenACC. Make sure
     * that the files are compiled correctly
     *
     * @param height int
     * @param width int
     * @param xVec int array: x coordinates of the points
     * @param yVec int array: y coordinates of the points
     * @param vecSize int: size of the vectors xVec and yVec
     * @return int array with values ranging from 0 to vecSize and size height * width.
     *         Each value correspond to a voronoi region e.g. [0, 0, 1] means that
     *         the first two values are in the region of point 0 and the last value
     *         is in the region of point 1.     **/
    static int *
    generateVoronoiDiagramACC(int height, int width, int *xVec, int *yVec, int vecSize);

    /**
     * Given two points (x1, y1) and (x2, y2), this method calculates the euclidiean distance of those two points
     * @param x1 int
     * @param y1 int
     * @param x2 int
     * @param y2 int
     * @return the distance as double
     */
    static double getDistance(int x1, int y1, int x2, int y2);

    /**
     * This methods compares two diagram arrays and returns true if they are the same
     * @param arr1 int array
     * @param arr2 int array
     * @param arrSize int: size of arr1/arr2
     * @return bool: true if arr1 equals arr 2 else false
     */
    static bool sameDiagram(int *arr1, int *arr2, int arrSize);
};

#endif //VORONOI_DIAGRAMME_VORONOIGENERATOR_H
