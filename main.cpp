//
// Created by abdallahdarwesh on 3/25/20.
//

#include <GL/glut.h>
#include "imageLoader.h"
#include "bodyParts.h"
#include <math.h>


GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;

GLfloat angle1 = -30;
GLfloat angle2 = -60;


GLfloat angle3 = -30;
GLfloat angle4 = -60;


static GLint choise = 0;

static GLfloat theta[17] = {0.0, 0.0, 0.0, 90.0,
                            -20.0, 90.0, -20.0, 180.0,
                            0.0, 180.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 0.0};

static GLfloat limits[17][2] = {
        {0,   0},
        {0,   0},
        {0,   0},
        {120, -90},
        {-20, -110},
        {120, -90},
        {-20, -110},
        {185, 120},
        {100, 0},
        {185, 120},
        {100, 0},
        {0,   -180},
        {180, 0},
        {70,  -5},
        {5,   -70},
        {90,  -120},
        {120, -90}
};

GLfloat eye[3] = {0.0, 0.0, 40.0};
GLfloat center[3] = {0.0, 0.0, 3};
GLfloat up[3] = {0.0, 1.0, 0.0};

GLfloat horizontal[3] = {0, 0, 0};
GLfloat look[3] = {0,0,0};


void crossProduct(GLfloat a[], GLfloat b[], GLfloat c[]) {
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(GLfloat a[]) {
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void rotatePoint(GLfloat a[], GLfloat theta, GLfloat p[]) {

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];

}

void Left() {
    // implement camera rotation arround vertical window screen axis to the left
    // used by mouse and left arrow
    rotatePoint(up, 0.1, eye);
}

void Right() {
    // implement camera rotation arround vertical window screen axis to the right
    // used by mouse and right arrow
    rotatePoint(up, -0.1, eye);
}


void Up() {
    // implement camera rotation arround horizontal window screen axis +ve
    // used by up arrow
    for (int i= 0;i<3;i++){
        look[i] = center[i] - eye[i];
    }
    crossProduct(look, up, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, 0.1, eye);
    rotatePoint(horizontal, 0.1, up);
}

void Down() {
    // implement camera rotation arround horizontal window screen axis
    for (int i= 0;i<3;i++){
        look[i] = center[i] - eye[i];
    }
    crossProduct(look, up, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -0.1, eye);
    rotatePoint(horizontal, -0.1, up);
}


void moveForward() {

    GLfloat direction[3] = {0, 0, 0};

    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] += direction[0] * 0.1;
    eye[1] += direction[1] * 0.1;
    eye[2] += direction[2] * 0.1;

    center[0] += direction[0] * 0.1;
    center[1] += direction[1] * 0.1;
    center[2] += direction[2] * 0.1;

    glutPostRedisplay();
}

void moveBack() {
    GLfloat direction[3] = {0, 0, 0};

    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] -= direction[0] * 0.1;
    eye[1] -= direction[1] * 0.1;
    eye[2] -= direction[2] * 0.1;

    center[0] -= direction[0] * 0.1;
    center[1] -= direction[1] * 0.1;
    center[2] -= direction[2] * 0.1;

    glutPostRedisplay();

}


void myDisplay(void) {
    glClearColor(1, 1, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2], up[0], up[1], up[2]);
    glColor3f(0.0, 0.0, 0.0);
    glColor3ub(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    torso();
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0, TORSO_HEIGHT, 0.0);
    neck();

    glBindTexture(GL_TEXTURE_2D, texture1);
    glTranslatef(0.0, NECK_HEIGHT + 0.5 * HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    head();

    glPopMatrix();//add JOINT_POINT_
    glPushMatrix();//add JOINT_POINT_

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(-0.85 * (TORSO_RADIUS + JOINT_POINT_RADIUS),
                 0.9 * TORSO_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(theta[3], 1.0, 0.0, 0.0);   // **
    glRotatef(theta[11], 0.0, 1.0, 0.0);
    glRotatef(theta[15], 0.0, 0.0, 1.0);
    left_upper_arm();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    left_lower_arm();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);

    // Lower Fingers

    finger_joint(0.0, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(0.0, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle1, 1, 0, 0);
    lower_finger();
    glPopMatrix();

    finger_joint(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle1, 1, 0, 0);
    lower_finger();
    glPopMatrix();

    finger_joint(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle1, 1, 0, 0);
    lower_finger();
    glPopMatrix();


    glPushMatrix();
    //Upper Fingers
    glRotatef(angle1, 1, 0, 0);
    glTranslated(0, 0, FINGER_HEIGHT);

    finger_joint(0.0, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(0.0, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle2, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    finger_joint(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle2, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    finger_joint(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle2, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.85 * (TORSO_RADIUS + JOINT_POINT_RADIUS),
                 0.9 * TORSO_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    glRotatef(theta[12], 0.0, 1.0, 0.0);
    glRotatef(theta[16], 0.0, 0.0, 1.0);
    right_upper_arm();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    right_lower_arm();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);

    // Lower Fingers

    finger_joint(0.0, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(0.0, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle3, 1, 0, 0);
    lower_finger();
    glPopMatrix();

    finger_joint(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle3, 1, 0, 0);
    lower_finger();
    glPopMatrix();

    finger_joint(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle3, 1, 0, 0);
    lower_finger();
    glPopMatrix();


    glPushMatrix();
    //Upper Fingers
    glRotatef(angle3, 1, 0, 0);
    glTranslated(0, 0, FINGER_HEIGHT);

    finger_joint(0.0, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(0.0, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle4, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    finger_joint(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle4, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    finger_joint(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);

    glPushMatrix();
    glTranslated(-LOWER_ARM_RADIUS / 2, -LOWER_ARM_RADIUS / 2, 0.0);
    glRotatef(angle4, 1, 0, 0);
    upper_finger();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTranslatef(-(TORSO_RADIUS - JOINT_POINT_RADIUS),
                 -0.15 * JOINT_POINT_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTranslatef(0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[7], 1.0, 0.0, 0.0);
    glRotatef(theta[13], 0.0, 0.0, 1.0);
    left_upper_leg();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    left_lower_leg();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, LOWER_LEG_HEIGHT, -0.5 * FOOT_HEIGHT);
    left_foot();

    glPopMatrix();
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTranslatef(TORSO_RADIUS - JOINT_POINT_RADIUS,
                 -0.15 * JOINT_POINT_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTranslatef(0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[9], 1.0, 0.0, 0.0);
    glRotatef(theta[14], 0.0, 0.0, 1.0);
    right_upper_leg();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    joint_point();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    right_lower_leg();

    glBindTexture(GL_TEXTURE_2D, texture4);
    glTranslatef(0.0, LOWER_LEG_HEIGHT, -0.5 * FOOT_HEIGHT);
    right_foot();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//--------------------------------Keyboard control function-----------------------
void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') { choise = 2; }         // Head horiz
    if (key == 'a') { choise = 1; }         // Head vert

    if (key == 'w') { choise = 3; }         //left arm horiz
    if (key == 's') { choise = 11; }        //left arm vert

    if (key == 'e') { choise = 5; }         //right arm horiz
    if (key == 'd') { choise = 12; }        //right arm horiz

    if (key == 'r') { choise = 7; }         //left leg vert
    if (key == 'f') { choise = 13; }        //left leg horiz

    if (key == 't') { choise = 9; }         //right leg horiz
    if (key == 'g') { choise = 14; }        //right leg vert

    if (key == 'z') { choise = 0; }         //torso

    if (key == 'x') { choise = 4; }         //left_lower_arm

    if (key == 'c') { choise = 6; }         //right_lower_arm

    if (key == 'v') { choise = 8; }         //left_lower_leg

    if (key == 'b') { choise = 10; }        //right_lowerleg

    if (key == 'o') { choise = 15; }

    if (key == 'p') { choise = 16; }


    if (key == '9') {
        if (choise == 0) {
            theta[choise] += 5.0;
            if (theta[choise] > 360) theta[choise] -= 360;
        } else {
            theta[choise] += 5.0;
            if (theta[choise] > limits[choise][0]) theta[choise] = limits[choise][0];
        }

        glutPostRedisplay();
    }

    if (key == '0') {
        if (choise == 0) {
            theta[choise] -= 5.0;
            if (theta[choise] < 360) theta[choise] += 360;
        } else {
            theta[choise] -= 5.0;
            if (theta[choise] < limits[choise][1]) theta[choise] = limits[choise][1];
        }
        glutPostRedisplay();
    }

    if (key == '1') {  // transform two hands together
        theta[11] -= 5.0;
        theta[12] += 5.0;
        if (theta[11] < limits[11][1]) theta[11] = limits[11][1];
        if (theta[12] > limits[12][0]) theta[12] = limits[12][0];
        glutPostRedisplay();
    }

    if (key == '2') {  // transform two hands together
        theta[11] += 5.0;
        theta[12] -= 5.0;
        if (theta[11] > limits[11][0]) theta[11] = limits[11][0];
        if (theta[12] < limits[12][1]) theta[12] = limits[12][1];
        glutPostRedisplay();
    }

    if (key == '3') {  // transform two hands together
        theta[15] -= 5.0;
        theta[16] += 5.0;
        if (theta[15] < limits[15][1]) theta[15] = limits[15][1];
        if (theta[16] > limits[16][0]) theta[16] = limits[16][0];
        glutPostRedisplay();
    }

    if (key == '4') {  // transform two hands together
        theta[15] += 5.0;
        theta[16] -= 5.0;
        if (theta[15] > limits[15][0]) theta[15] = limits[15][0];
        if (theta[16] < limits[16][1]) theta[16] = limits[16][1];
        glutPostRedisplay();
    }

    if (key == '5') {  // transform two hands together
        theta[4] += 5.0;
        theta[6] += 5.0;
        if (theta[4] > limits[6][0]) theta[4] = limits[4][0];
        if (theta[6] > limits[6][0]) theta[6] = limits[6][0];
        glutPostRedisplay();
    }

    if (key == '6') {  // transform two hands together
        theta[4] -= 5.0;
        theta[6] -= 5.0;
        if (theta[4] < limits[4][1]) theta[4] = limits[6][1];
        if (theta[6] < limits[6][1]) theta[6] = limits[4][1];
        glutPostRedisplay();
    }

    if (key == '7') {
        moveForward();
    }

    if (key == '8') {
        moveBack();
    }


}

static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        Left();
        glutPostRedisplay();
    }
    if (button == GLUT_RIGHT_BUTTON){
        Right();
        glutPostRedisplay();
    }

}



void myReshape(int w, int h) {
    glViewport(0, 0, w, h); //Mapping Drawing Coordinates to Window Coordinates
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-30.0, 30.0, -30.0 * (GLfloat) h / (GLfloat) w,
                30.0 * (GLfloat) h / (GLfloat) w, -200, 200);
    else
        glOrtho(-30.0 * (GLfloat) w / (GLfloat) h,
                30.0 * (GLfloat) w / (GLfloat) h, -30.0, 30.0, -200, 200);

    gluPerspective(1.0, (float) w / h, 2.0, 1.0);
//    gluLookAt(eye[0], eye[1], eye[2],
//              center[0], center[1], center[2], up[0], up[1], up[2]);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void redisplay_all(void) {
    myReshape(WIN_WIDTH, WIN_HEIGHT);
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            Left();
            break;
        case GLUT_KEY_RIGHT:
            Right();
            break;
        case GLUT_KEY_UP:
            Up();
            break;
        case GLUT_KEY_DOWN:
            Down();
            break;
    }

    glutPostRedisplay();
}


//--------------------------------Initialization function----------------------------
void myInit() {
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {100.0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Image *image = loadBMP(
            "/home/abdallahdarwesh/CLionProjects/CG-Tasks/sbe306b-2020-assign-3-cameramovement-AbdallahDrwesh/textures/photom.bmp");
    Image *image1 = loadBMP(
            "/home/abdallahdarwesh/CLionProjects/CG-Tasks/sbe306b-2020-assign-3-cameramovement-AbdallahDrwesh/textures/body.bmp");
    Image *image2 = loadBMP(
            "/home/abdallahdarwesh/CLionProjects/CG-Tasks/sbe306b-2020-assign-3-cameramovement-AbdallahDrwesh/textures/shorts.bmp");
    Image *image3 = loadBMP(
            "/home/abdallahdarwesh/CLionProjects/CG-Tasks/sbe306b-2020-assign-3-cameramovement-AbdallahDrwesh/textures/skin.bmp");


    glGenTextures(1, &texture2);
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture3);
    glGenTextures(1, &texture4);

    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                      image1->width,
                      image1->height,
                      GL_RGB, GL_UNSIGNED_BYTE,
                      image1->pixels);

    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                      image->width,
                      image->height,
                      GL_RGB, GL_UNSIGNED_BYTE,
                      image->pixels);

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                      image2->width,
                      image2->height,
                      GL_RGB, GL_UNSIGNED_BYTE,
                      image2->pixels);


    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                      image3->width,
                      image3->height,
                      GL_RGB, GL_UNSIGNED_BYTE,
                      image3->pixels);

    delete image;
    delete image1;
    delete image2;
    delete image3;

    fill_objects();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Humanoid");
    myInit();
    glutReshapeFunc(myReshape);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    redisplay_all();
    glutMainLoop();
    return 0;
}


/*
 * // Clear the window with current clearing color
 * glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
 *
 * // Refreshing the Display
 * glutPostRedisplay()
 *
 *
 *
 */
