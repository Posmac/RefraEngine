#ifndef REFRAENGINE_MESHLOADER_H
#define REFRAENGINE_MESHLOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>

#include "Mesh.h"

namespace rfe
{
    class MeshLoader
    {
    public:
        int LoadMesh(std::string path, Mesh& mesh);
    };
}

#endif //REFRAENGINE_MESHLOADER_H
