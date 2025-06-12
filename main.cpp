// main.cpp

#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <string>


void load_mesh(std::string fileName);

void init_timer();
void display();


void reshape(int w, int h)
{

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1,  
        -0.1, 0.1, 
        0.1, 1000.0);

    // 3) 모델뷰로 복귀
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("OpenGL Bunny: Loading...");


    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    load_mesh("bunny.obj");
    init_timer();


    glEnable(GL_DEPTH_TEST);   



    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // 1) 전역 ambient Ia = (0.2,0.2,0.2)
    GLfloat globalIa[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalIa);

    // 2) 방향광 LIGHT0: ambient=(0,0,0), diffuse=(1,1,1), specular=(0,0,0)
    GLfloat La[4] = { 0, 0, 0, 1.0f };
    GLfloat Ld[4] = { 1, 1, 1, 1.0f };
    GLfloat Ls[4] = { 0, 0, 0, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, La);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Ld);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Ls);

    // 3) 머티리얼: ka=kd=(1,1,1), ks=0, shininess=0
    GLfloat white[4] = { 1, 1, 1, 1 };
    glMaterialfv(GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE,
        white);
    glMaterialf(GL_FRONT_AND_BACK,
        GL_SHININESS,
        0.0f);

    // --- 콜백 등록 ---
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // instead of posting inside display(), do:
    glutIdleFunc(display);
    // --- 메인 루프 진입 ---
    glutMainLoop();
    return 0;
}
