#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <float.h>

#include "load_mesh.h"        
#include "frame_timer.h"        
#include "init_vertex_array.h"   


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-0.1, 0.1,
        -0.1, 0.1,
        0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("OpenGL Bunny Q2: VAO/VBO");

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to init GLEW\n");
        return 1;
    }

    load_mesh("bunny.obj");
    init_timer();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    GLfloat Ia[4] = { 0.2f,0.2f,0.2f,1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ia);

    GLfloat La[4] = { 0,0,0,1 }, Ld[4] = { 1,1,1,1 }, Ls[4] = { 0,0,0,1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, La);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Ld);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Ls);

    GLfloat white[4] = { 1,1,1,1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);


    init_vertex_array();

 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);  


    glutMainLoop();
    return 0;
}