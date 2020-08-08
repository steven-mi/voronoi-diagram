#include <fstream>
#include "FileReader.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

std::vector<std::vector<int>> FileReader::readFilePath(const std::string &filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        // count amount of points
        int count = 0;
        std::string line;
        while (getline(file, line)) {
            count++;
        }
        file.close();

        std::ifstream file(filePath);
        std::vector<std::vector<int>> result = std::vector<std::vector<int>>(count, std::vector<int>(2, 0));;
        int i = 0;
        while (std::getline(file, line)) {
            // store each number in the line into a vector temp
            std::vector<int> temp;
            int number;
            std::stringstream iss(line);
            while (iss >> number)
                temp.push_back(number);
            if (temp.size() > 2) {
                std::cout << "FileNotCorrectError: File has more than 2 numbers in a line\n";
                return std::vector<std::vector<int>>();
            }

            // append temp vector to result
            result[i] = temp;
            i++;
        }
        return result;
    }else{
        return std::vector<std::vector<int>>();
    }
}

void FileReader::createPGM(int *vec, std::vector<std::vector<int>> colorCodes, int height, int width) {
    FILE *imageFile;

    imageFile = fopen("voronoi.pgm", "wb");
    if (imageFile == nullptr) {
        perror("ERROR: Cannot open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(imageFile, "P3\n");           // P5 filetype
    fprintf(imageFile, "%d %d\n", width, height);   // dimensions
    fprintf(imageFile, "255\n");          // Max pixel

    /* Now write a greyscale ramp */
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            int colorIndex = vec[h * width + w];
            int r = colorCodes[colorIndex][0], g = colorCodes[colorIndex][1], b = colorCodes[colorIndex][2];

            fprintf(imageFile, "%d %d %d\t", r, g, b);
        }
        fprintf(imageFile, "\n");
    }
    fclose(imageFile);
}
