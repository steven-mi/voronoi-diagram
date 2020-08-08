#include "gtest/gtest.h"
#include "generator/VoronoiGenerator.h"
#include "utils/VectorUtils.h"

TEST(VoronoiGeneratorTest, generateVoronoiDiagramCorrectly) {
    int size = 2;
    int xArr[] = {0, 0, 1, 1};
    int yArr[] = {0, 1, 0, 1};

    int *diagram =
            VoronoiGenerator::generateVoronoiDiagram(size, size, xArr, yArr, 4);
    int correctDiagram[] = {0, 1, 2, 3};

    bool same = VoronoiGenerator::sameDiagram(diagram, correctDiagram, size * size);
    ASSERT_TRUE(same);
}

TEST(VoronoiGeneratorTest, generateVoronoiDiagramOMPCorrectly) {
    int size = 2;
    int xArr[] = {0, 0, 1, 1};
    int yArr[] = {0, 1, 0, 1};

    int *diagram =
            VoronoiGenerator::generateVoronoiDiagramOMP(size, size, xArr, yArr, 4);
    int correctDiagram[] = {0, 1, 2, 3};

    bool same = VoronoiGenerator::sameDiagram(diagram, correctDiagram, size * size);
    ASSERT_TRUE(same);
}

TEST(VoronoiGeneratorTest, generateVoronoiDiagramACCCorrectly) {
    int size = 2;
    int xArr[] = {0, 0, 1, 1};
    int yArr[] = {0, 1, 0, 1};

    int *diagram =
            VoronoiGenerator::generateVoronoiDiagramACC(size, size, xArr, yArr, 4);
    int correctDiagram[] = {0, 1, 2, 3};

    bool same = VoronoiGenerator::sameDiagram(diagram, correctDiagram, size * size);
    ASSERT_TRUE(same);
}

TEST(VoronoiGeneratorTest, OpenMPParallizedCorrectly) {
    int nPoints = 10;
    int size = 1000;
    std::vector<int> xVec = VectorUtils::generateRandomVector(nPoints, size);;
    std::vector<int> yVec = VectorUtils::generateRandomVector(nPoints, size);;

    int xArr[xVec.size()];
    std::copy(xVec.begin(), xVec.end(), xArr);
    int yArr[yVec.size()];
    std::copy(yVec.begin(), yVec.end(), yArr);

    int *diagram =
            VoronoiGenerator::generateVoronoiDiagram(size, size, xArr, yArr, xVec.size());
    int *diagramOMP =
            VoronoiGenerator::generateVoronoiDiagramOMP(size, size, xArr, yArr, xVec.size());
    bool same = VoronoiGenerator::sameDiagram(diagram, diagramOMP, size * size);
    ASSERT_TRUE(same);
}

TEST(VoronoiGeneratorTest, OpenACCParallizedCorrectly) { // 12/2/2020 -> 737761
    int nPoints = 10;
    int size = 1000;
    std::vector<int> xVec = VectorUtils::generateRandomVector(nPoints, size);;
    std::vector<int> yVec = VectorUtils::generateRandomVector(nPoints, size);;

    int xArr[xVec.size()];
    std::copy(xVec.begin(), xVec.end(), xArr);
    int yArr[yVec.size()];
    std::copy(yVec.begin(), yVec.end(), yArr);

    int *diagram =
            VoronoiGenerator::generateVoronoiDiagram(size, size, xArr, yArr, xVec.size());
    int *diagramOMP =
            VoronoiGenerator::generateVoronoiDiagramACC(size, size, xArr, yArr, xVec.size());
    bool same = VoronoiGenerator::sameDiagram(diagram, diagramOMP, size * size);
    ASSERT_TRUE(same);
}

