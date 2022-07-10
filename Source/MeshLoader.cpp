#include "MeshLoader.h"

int rfe::MeshLoader::LoadMesh(std::string path, Mesh &mesh) {
    std::fstream fstream(path);
    if (!fstream.is_open()) {
        std::cout << "The file path isn`t correct" << std::endl;
        return 0;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    std::map<std::string ,rfe::VertexDataPTN> vertexDataMap;

    int index = 0;
    std::string fileLine;
    std::string dataType;

    while (getline(fstream, fileLine)) {

        if (fileLine[0] != 'v' && fileLine[0] != 'f') {
            continue;
        }

        std::stringstream stringstream(fileLine);
        stringstream >> dataType;
        if (dataType == "v") {
            float x, y, z;
            stringstream >> x >> y >> z;
            positions.emplace_back(x, y, z);
        }
        if (dataType == "vt") {
            float x, y;
            stringstream >> x >> y;
            textureCoords.emplace_back(x, y);
        }
        if (dataType == "vn") {
            float x, y, z;
            stringstream >> x >> y >> z;
            normals.emplace_back(x, y, z);
        }
        if (dataType == "f") {
            for (int i = 0; i < 3; i++) {
                std::string faceTriplet;
                stringstream >> faceTriplet;
                std::stringstream tripletSS(faceTriplet);
                int v, t, n;
                char ignore;
                tripletSS >> v >> ignore >> t >> ignore >> n;
                rfe::VertexDataPTN vertexDataPtn(positions[--v],
                                                 normals[--n],
                                                 textureCoords[--t]);

                if (vertexDataMap.count(faceTriplet) == 0) {
                    vertexDataMap[faceTriplet] = vertexDataPtn;
                    mesh.AddVertexData(vertexDataPtn);
                    mesh.AddIndex(index);
                    index++;
                } else {
                    mesh.AddIndex(index);
                }
            }
        }
    }
}
