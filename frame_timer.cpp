#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <cstdio>

// ── Forward declarations for mesh data defined in load_mesh.cpp ──
struct Vector3 { float x, y, z; };
struct Triangle { unsigned int indices[3]; };
extern std::vector<Vector3>  gPositions;
extern std::vector<Vector3>  gNormals;
extern std::vector<Triangle> gTriangles;

// ── GPU timer and accumulators ──
static GLuint gTimer = 0;
static float  gTotalTimeElapsed = 0.0f;
static int    gTotalFrames = 0;


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
    GLint timeElapsedNano = 0;
    glGetQueryObjectiv(gTimer, GL_QUERY_RESULT, &timeElapsedNano);
    // nanoseconds → seconds
    return timeElapsedNano * 1e-9f;
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
    glTranslatef(0.1f, -1.0f, -1.5f);
    glScalef(10.0f, 10.0f, 10.0f);


    start_timing();
    glBegin(GL_TRIANGLES);
    for (const Triangle& tri : gTriangles) {
        for (int v = 0; v < 3; ++v) {
            unsigned int i = tri.indices[v];
            glNormal3f(gNormals[i].x, gNormals[i].y, gNormals[i].z);
            glVertex3f(gPositions[i].x, gPositions[i].y, gPositions[i].z);
        }
    }
    glEnd();
    float dt = stop_timing();


    gTotalFrames++;
    gTotalTimeElapsed += dt;
    float fps = gTotalFrames / gTotalTimeElapsed;
    char title[64];
    sprintf(title, "OpenGL Bunny: %.2f FPS", fps);
    glutSetWindowTitle(title);

    glutSwapBuffers();
}