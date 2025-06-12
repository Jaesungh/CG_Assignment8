#define _CRT_SECURE_NO_WARNINGS

#include "load_mesh.h"
#include <fstream>
#include <float.h>        
#include <cstdlib>        
#include <algorithm>        
#include <cstring>          
#include <cstdio>

std::vector<Vector3>  gPositions;
std::vector<Vector3>  gNormals;
std::vector<Triangle> gTriangles;


static void tokenize(char* str, std::vector<std::string>& tokens, const char* delim) {
    char* tok = std::strtok(str, delim);
    while (tok) {
        tokens.emplace_back(tok);
        tok = std::strtok(nullptr, delim);
    }
}

static int face_index(const char* s) {
    return std::atoi(s);  
}


void load_mesh(const std::string& fileName) {
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::fprintf(stderr, "ERROR: Unable to load mesh from %s\n", fileName.c_str());
        std::exit(1);
    }


    gPositions.clear();
    gNormals.clear();
    gTriangles.clear();


    float xmin = FLT_MAX, xmax = -FLT_MAX;
    float ymin = FLT_MAX, ymax = -FLT_MAX;
    float zmin = FLT_MAX, zmax = -FLT_MAX;

    char line[1024];
    while (fin.getline(line, sizeof(line))) {
        if (std::strlen(line) <= 1) continue;
        std::vector<std::string> tokens;
        tokenize(line, tokens, " ");

        if (tokens[0] == "v") {
            float x = std::atof(tokens[1].c_str());
            float y = std::atof(tokens[2].c_str());
            float z = std::atof(tokens[3].c_str());
            xmin = std::min(x, xmin); xmax = std::max(x, xmax);
            ymin = std::min(y, ymin); ymax = std::max(y, ymax);
            zmin = std::min(z, zmin); zmax = std::max(z, zmax);
            gPositions.push_back({ x,y,z });
        }
        else if (tokens[0] == "vn") {
            float x = std::atof(tokens[1].c_str());
            float y = std::atof(tokens[2].c_str());
            float z = std::atof(tokens[3].c_str());
            gNormals.push_back({ x,y,z });
        }
        else if (tokens[0] == "f") {
            unsigned int a = face_index(tokens[1].c_str()) - 1;
            unsigned int b = face_index(tokens[2].c_str()) - 1;
            unsigned int c = face_index(tokens[3].c_str()) - 1;
            gTriangles.push_back({ {a,b,c} });
        }
    }
    fin.close();

    std::printf("Loaded mesh from %s. (%zu vertices, %zu normals, %zu triangles)\\n",
        fileName.c_str(),
        gPositions.size(),
        gNormals.size(),
        gTriangles.size());
    std::printf("Bounding box: (%.4f,%.4f,%.4f) to (%.4f,%.4f,%.4f)\\n",
        xmin, ymin, zmin, xmax, ymax, zmax);
}
