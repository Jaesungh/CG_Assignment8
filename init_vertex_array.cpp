#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GL/glut.h>       
#include <vector>
#include "load_mesh.h"


GLuint  gVAO = 0;
GLsizei gIndexCount = 0;

void init_vertex_array() {
    std::vector<unsigned int> indices;
    indices.reserve(gTriangles.size() * 3);
    for (auto& tri : gTriangles) {
        indices.push_back(tri.indices[0]);
        indices.push_back(tri.indices[1]);
        indices.push_back(tri.indices[2]);
    }
    gIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);


    GLuint posVBO;
    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER,
        gPositions.size() * sizeof(Vector3),
        gPositions.data(),
        GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vector3), (void*)0);

    GLuint normVBO;
    glGenBuffers(1, &normVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normVBO);
    glBufferData(GL_ARRAY_BUFFER,
        gNormals.size() * sizeof(Vector3),
        gNormals.data(),
        GL_STATIC_DRAW);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(Vector3), (void*)0);


    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    glBindVertexArray(0);
}
