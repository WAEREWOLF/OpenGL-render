#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <math.h>

/* Global variables */
double rx = 34, ry = -2.6, rz = 36.6;
double px = 0, py = 0, pz = 0;

double ball_Y = 10.0;
bool move_up = true;
double height = 10.0;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-10 + rx, 9 + ry, -10 + rz,
        px, py, pz,
        0, 1, 0);
    glPushMatrix();

    for (double i = -20; i < 20; i += 1.1) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_STRIP);
        glVertex3f(i, 0, -20);
        glVertex3f(i, 0, 20);
        glEnd();
    }

    for (double i = -20; i < 20; i += 1.1) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_STRIP);
        glVertex3f(-20, 0, i);
        glVertex3f(20, 0, i);
        glEnd();
    }

    // eyes
    // y 
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);
    glEnd();

    // x
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);
    glEnd();

    // z
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();

    // balls
    glColor3f(1, 0, 0); // red dummy
    glutSolidSphere(0.0, 500, 500);
    glTranslatef(7, ball_Y, 0);
    glEnd();

    glColor3f(0, 1, 0); // green
    glutSolidSphere(0.84, 500, 500);
    glTranslatef(10, ball_Y, 4);
    glEnd();

    glColor3f(1, 1, 1); // white
    glutSolidSphere(0.84, 500, 500);
    glTranslatef(-10, ball_Y, -9);
    glEnd();

    glColor3f(1, 0, 1); // purple
    glutSolidSphere(0.84, 500, 500);
    glTranslatef(10, ball_Y, 9);
    glEnd();

    glColor3f(0, 1, 1); // blue
    glutSolidSphere(2, 500, 500);
    glTranslatef(-43, ball_Y, -6);
    glEnd();

    

    glPopMatrix();
    glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void cameraMovementNormalKeywords(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // esc
        exit(0);
        break;
        // eye x
    case 'd':
        rx += 0.2;
        std::cout <<" rx: "<< rx <<" px: "<<px<<" py: "<<py<<" ry: "<<ry<< " rz: "<<rz<<" pz: "<<pz<<'\n';
        break;
    case 'a':
        rx -= 0.2;
        break;
    case 'l':
        px += 0.8;
        break;
    case 'j':
        px -= 0.2;
        break;
        // eye y
    case 'q':
        ry += 0.2;
        break;
    case 'e':
        ry -= 0.2;
        break;
    case 'u':
        py += 0.2;
        break;
    case 'o':
        py -= 0.2;
        break;
    case 49: // 1
        ry += 0.2;
        py += 0.2;
        break;
    case 50: // 2
        ry -= 0.2;
        py -= 0.2;
        break;
        // eye z
    case 'w':
        rz += 0.2;
        break;
    case 's':
        rz -= 0.2;
        break;
    case 'i':
        pz += 0.8;
        break;
    case 'k':
        pz -= 0.8;
        break;
    }
    glutPostRedisplay();
}

void cameraMovementArrowKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        rx += 0.2;
        px += 0.2;
        break;
    case GLUT_KEY_LEFT:
        rx -= 0.2;
        px -= 0.2;
        break;
    case GLUT_KEY_UP:
        rz += 0.2;
        pz += 0.2;
        break;
    case GLUT_KEY_DOWN:
        rz -= 0.2;
        pz -= 0.2;
        break;
    }
    glutPostRedisplay();
}

// request to draw the next frame
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

void bounceBall() {
    if (ball_Y == 0 || ball_Y == height) {
        move_up ^= 1;
    }

    if (move_up) {
        ball_Y += 0.5;
    }
    else {
        ball_Y -= 0.5;
    }

    glutTimerFunc(35, timer, 0);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {


    // init GLUT and create window
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Enable double buffered mode
    glutInitWindowSize(1000, 800);   // Set the window's initial width & height
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    glutCreateWindow("Bouncing Balls");          // Create window with the given title
    initGL();                       // Our own OpenGL initialization

    // register callbacks
    glutDisplayFunc(display); 
    glutIdleFunc(bounceBall);
    
    // Register callback handler for window re-paint event
    glutKeyboardFunc(cameraMovementNormalKeywords);
    glutSpecialFunc(cameraMovementArrowKeys);
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event

    // enter GLUT event processing cycle
    glutMainLoop();                 // Enter the infinite event-processing loop
}