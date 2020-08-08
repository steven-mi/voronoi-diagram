#include <iostream>
#include <chrono>
#include "utils/VectorUtils.h"
#include "utils/FileReader.h"
#include "generator/VoronoiGenerator.h"
#include <regex>

#define DEFAULTPOINTS 100
#define DEFAULTHEIGHT 1000
#define DEFAULTWIDTH 1000
#define DEFAULTTYPE "SEQUENTIAL"

static void show_usage(std::string name) {
    std::cerr << "Usage: " << name << "<option(s)> SOURCES"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-np,--npoints NPOINTS\tSpecify the amount of random points to be used. (default 100) \n"
              << "\t-pf,--pointFile POINTFILE\tSpecify path to a file with points defined. If this is used, then npoints wont be used.\n"
              << "\t-h,--height HEIGHT\tSpecify height of the output image (default 1000)\n"
              << "\t-w,--width WIDTH\tSpecify width of the output image (default 1000)\n"
              << "\t-t,--type TYPE\tSpecify the calculation type. You can choose between SEQUENTIAL, OPENMP, OPENACC. Make sure that the app is compiled correctly. (default SEQUENTIAL)\n"
              << std::endl;
}


int main(int argc, char *argv[]) {
    int height = DEFAULTHEIGHT;
    int width = DEFAULTWIDTH;
    int nPoints = DEFAULTPOINTS;
    std::string type = DEFAULTTYPE;
    std::string pointPath = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--help") {
            show_usage(argv[0]);
            return 0;
        }

        if ((arg == "-h") || (arg == "--height")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                height = std::stoi(argv[i + 1]);
            }else{
                show_usage(argv[0]);
                return 0;
            }
        } else if ((arg == "-w") || (arg == "--width")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                width = std::stoi(argv[i + 1]);
            }
        } else if ((arg == "-np") || (arg == "--npoints")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                nPoints = std::stoi(argv[i + 1]);
            }
        } else if ((arg == "-pf") || (arg == "--pointFile")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                pointPath = argv[i + 1];
            }
        } else if ((arg == "-t") || (arg == "--type")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                if (std::string(argv[i + 1]).compare("SEQUENTIAL") == 0 ||
                    std::string(argv[i + 1]).compare("OPENMP") == 0 ||
                    std::string(argv[i + 1]).compare("OPENACC") == 0) {
                    type = argv[i + 1]; // Increment 'i' so we don't get the argument as the next argv[i].
                }
            }
        }
        i++;
    }

    std::vector<int> xVec;
    std::vector<int> yVec;

    if (pointPath.empty()) {
        xVec = VectorUtils::generateRandomVector(nPoints, height);
        yVec = VectorUtils::generateRandomVector(nPoints, width);
    } else {
        std::vector<std::vector<int>> pointVec = FileReader::readFilePath(pointPath);
        if (pointVec.empty()) {
            std::cout << "FileNotFoundError: File could not be found!\n";
            return 1;
        }

        xVec = std::vector<int>(pointVec.size(), 0);
        yVec = std::vector<int>(pointVec.size(), 0);
        for (int i = 0; i < pointVec.size(); i++) {
            for (int j = 0; j < pointVec[0].size(); j++) {
                if (j == 0) {
                    xVec[i] = pointVec[i][j];
                } else if (j == 1) {
                    yVec[i] = pointVec[i][j];
                }
            }
        }
    }

    int xArr[xVec.size()];
    std::copy(xVec.begin(), xVec.end(), xArr);
    int yArr[yVec.size()];
    std::copy(yVec.begin(), yVec.end(), yArr);

    int *diagram;
    if (type == "SEQUENTIAL") {
        auto t0 = std::chrono::high_resolution_clock::now();
        diagram =
                VoronoiGenerator::generateVoronoiDiagram(height, width, xArr, yArr, xVec.size());
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> t0_t1 = t1 - t0;
        std::cout << type << " took:" << t0_t1.count() << "s\n";
    } else if (type == "OPENMP") {
        auto t0 = std::chrono::high_resolution_clock::now();
        diagram =
                VoronoiGenerator::generateVoronoiDiagramOMP(height, width, xArr, yArr, xVec.size());
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> t0_t1 = t1 - t0;
        std::cout << type << " took:" << t0_t1.count() << "s\n";
    }
    if (type == "OPENACC") {
        auto t0 = std::chrono::high_resolution_clock::now();
        diagram =
                VoronoiGenerator::generateVoronoiDiagramACC(height, width, xArr, yArr, xVec.size());
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> t0_t1 = t1 - t0;
        std::cout << type << " took:" << t0_t1.count() << "s\n";
    }

    std::vector<std::vector<int>> colorCodes = VectorUtils::generateRandomVector2D(xVec.size() + 1, 3, 255);
    FileReader::createPGM(diagram, colorCodes, height, width);
    
    exit(0);
}

