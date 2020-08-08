/**
 * This class is has some utility functions about saving and storing files.
 */

#ifndef VORONOI_DIAGRAMME_FILEREADER_H
#define VORONOI_DIAGRAMME_FILEREADER_H


#include <string>
#include <vector>

class FileReader {
public:
    /**
     * This method gets the path of a file with points and returns a two-dimensional array with the
     * points.
     * Example:
     * >ls input.txt
     * 0 1
     * 20 1
     * std::vector<std::vector<int>> points = readFilePath("input.txt)
     * std::cout << points[0][0]; 0
     * std::cout << points[0][1]; 1
     * std::cout << points[1][0]; 20
     * std::cout << points[0][1]; 1

     * @param filePath string
     * @return std::vector<std::vector<int>>
     */
    static std::vector<std::vector<int>> readFilePath(const std::string &filePath);

    /**
     * This methods gets our one-dimensional voronoi diagramm array and produces a PGM. The colors are
     * defined in the two dimensional vector colorCodes. The output PGM file is stored in the current
     * folder under the game voronoi.ppgm.
     *
     * @param vec int array: one-dimensional int array with size height * width
     * @param colorCodes: two-dimensional int array with size (n, 3)
     * @param height int
     * @param width int
     */
    static void createPGM(int *vec, std::vector<std::vector<int>> colorCodes, int height, int width);

};


#endif //VORONOI_DIAGRAMME_FILEREADER_H
