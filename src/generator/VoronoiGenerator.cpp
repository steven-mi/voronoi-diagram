#include "VoronoiGenerator.h"
#include <limits>
#include <math.h>
#include <utility>

#pragma acc routine seq

double VoronoiGenerator::getDistance(int x1, int y1, int x2, int y2) {
    double x_norm = (x2 - x1) * (x2 - x1) * 1.0;
    double y_norm = (y2 - y1) * (y2 - y1) * 1.0;
    double norm_add = x_norm + y_norm;
    return sqrt(norm_add);
}

int *VoronoiGenerator::generateVoronoiDiagramACC(int height, int width, int *xVec, int *yVec, int vecSize) {
    int *vec = (int *) malloc(height * width * sizeof(int));

#pragma acc parallel loop collapse(2) copy(vec[0:height*width - 1]) copyin(xVec[:vecSize], yVec[:vecSize])
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            double minDis = std::numeric_limits<double>::max();
            int minIndex = -1;

#pragma acc copyin(xVec[:vecSize], yVec[:vecSize])
            for (int index = 0; index < vecSize; index++) {
                double dis = getDistance(h, w, xVec[index], yVec[index]);

                if (dis < minDis) {
                    minDis = dis;
                    minIndex = index;
                }
            }
            vec[h * width + w] = minIndex;
        }
    }
    return vec;
}

int *VoronoiGenerator::generateVoronoiDiagram(int height, int width, int *xVec, int *yVec, int vecSize) {
    int *vec = (int *) malloc(height * width * sizeof(int));

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            double minDis = std::numeric_limits<double>::max();
            int minIndex = -1;

            for (int index = 0; index < vecSize; index++) {
                double dis = getDistance(h, w, xVec[index], yVec[index]);

                if (dis < minDis) {
                    minDis = dis;
                    minIndex = index;
                }
            }
            vec[h * width + w] = minIndex;
        }
    }
    return vec;
}

typedef std::pair<unsigned int, double> IndexValuePair;

IndexValuePair myMin(IndexValuePair a, IndexValuePair b) {
    return a.second < b.second ? a : b;
}

int *VoronoiGenerator::generateVoronoiDiagramOMP(int height, int width, int *xVec, int *yVec, int vecSize) {
    int *vec = (int *) malloc(height * width * sizeof(int));

#pragma omp parallel for
    for (int h = 0; h < height; h++) {
#pragma omp parallel for
        for (int w = 0; w < width; w++) {
            IndexValuePair minValueIndex(0, std::numeric_limits<double>::max());

#pragma omp declare reduction(minPair:IndexValuePair:omp_out=myMin(omp_out, omp_in)) initializer(omp_priv = IndexValuePair(0, std::numeric_limits<double>::max()))

#pragma omp parallel for reduction(minPair:minValueIndex)
            for (int index = 0; index < vecSize; index++) {
                double dis = getDistance(h, w, xVec[index], yVec[index]);
                if (dis < minValueIndex.second) {
                    minValueIndex.first = index;
                    minValueIndex.second = dis;
                }
            }
            vec[h * width + w] = minValueIndex.first;
        }
    }
    return vec;
}

bool VoronoiGenerator::sameDiagram(int *arr1, int *arr2, int arrSize) {
    int equal = 1;
    for (int i = 0; i < (arrSize); i++) {
        equal = arr1[i] - arr2[i];
        if (equal == 1) {
            return false;
        }
    }
    return true;
}






