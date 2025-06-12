#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <cstdio>

#include "load_mesh.h" 
#include "init_vertex_array.h"


static GLuint  gTimer = 0;
static float   gTotalTimeElapsed = 0.0f;
static int     gTotalFrames = 0;


void init_timer() {
    glGenQueries(1, &gTimer);
}

void start_timing() {
    glBeginQuery(GL_TIME_ELAPSED, gTimer);
}

float stop_timing() {
    glEndQuery(GL_TIME_ELAPSED);
    GLint available = 0;
    while (!available)
        glGetQueryObjectiv(gTimer, GL_QUERY_RESULT_AVAILABLE, &available);
    GLint timeNano = 0;
    glGetQueryObjectiv(gTimer, GL_QUERY_RESULT, &timeNano);
    return timeNano * 1e-9f;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);


    GLfloat lightDir[4] = { -1,-1,-1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);

    glTranslatef(0.1f, -1.0f, -1.5f);
    glScalef(10.0f, 10.0f, 10.0f);


    start_timing();
    glBindVertexArray(gVAO);
    glDrawElements(GL_TRIANGLES, gIndexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    float dt = stop_timing();


    gTotalFrames++;
    gTotalTimeElapsed += dt;
    float fps = gTotalFrames / gTotalTimeElapsed;
    char title[64];
    std::sprintf(title, "OpenGL Bunny: %.2f FPS", fps);
    glutSetWindowTitle(title);

    glutSwapBuffers();
}
