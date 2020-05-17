//
// Created by abdallahdarwesh on 3/25/20.
//

#include "bodyParts.h"

#include <GL/glut.h>


GLUquadricObj *t,   *h,   *n,    *lh,
        *rh,   *lf,  *rf,   *jp,
        *lhnd, *lft, *lua,  *lla,
        *rua,  *rla, *lll,  *rll,
        *rul,  *lul, *rhnd, *rft;




void head() {
    glPushMatrix();
    glColor3f(1.0, 0.0, 5.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glScalef(HEAD_HEIGHT, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h, 1.0, 10, 10);
    glPopMatrix();
}

void neck() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(n, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT, 10, 10);
    glPopMatrix();
}

void torso() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 8, 8);
    glPopMatrix();
}

void joint_point() {
    glPushMatrix();
    glScalef(JOINT_POINT_RADIUS, JOINT_POINT_HEIGHT,
             JOINT_POINT_RADIUS);
    gluSphere(jp, 1.0, 10, 10);
    glPopMatrix();
}

void finger_joint(GLfloat x , GLfloat y, GLfloat z){
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(1.2*FINGER_RADIUS,1.2*FINGER_RADIUS ,
             1.2*FINGER_RADIUS);
    gluSphere(jp, 1.0, 10, 10);
    glPopMatrix();
}

void left_upper_arm() {
    glPushMatrix();
    gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS,
                UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_arm() {
    glPushMatrix();
    glRotatef(0.0, 1.0, 0.0, 0.0);
    gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS,
                LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void upper_finger() {
    glPushMatrix();
    gluCylinder(lhnd, .1, .1, 1.3 * FINGER_HEIGHT, 10, 10);
    glPopMatrix();
}

void lower_finger() {
    glPushMatrix();
    gluCylinder(lhnd, .1, .1, FINGER_HEIGHT, 10, 10);
    glPopMatrix();
}


//void thumb(GLfloat x , GLfloat y, GLfloat z){
//    glPushMatrix();
//    finger_joint(x,y,z);
//
//
//    glTranslatef(x,y,z);
//    glRotatef(angle1,1,0,0);
//    gluCylinder(lhnd, .1, .1, FINGER_HEIGHT, 10, 10);
//
//
//    glTranslated(0, 0, FINGER_HEIGHT);
//    finger_joint(0,0,0);
//
//    glRotatef(90,1,0,0);
//    gluCylinder(lhnd, .1, .1, 1.2 * FINGER_HEIGHT, 10, 10);
//
//    glPopMatrix();
//}



void right_upper_arm() {
    glPushMatrix();
    gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS,
                UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_arm() {
    glPushMatrix();
    gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS,
                LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_upper_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS,
                UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS,
                LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_foot() {
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(FOOT_RADIUS, FOOT_HEIGHT, FOOT_RADIUS);
    gluSphere(lft, 1.0, 10, 10);
    glPopMatrix();
}

void right_upper_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS,
                UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS,
                LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_foot() {
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(FOOT_RADIUS, FOOT_HEIGHT, FOOT_RADIUS);
    gluSphere(rft, 1.0, 10, 10);
    glPopMatrix();
}


void fill_objects(){
    h = gluNewQuadric();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(h, GL_TRUE);
    gluQuadricDrawStyle(h, GLU_FILL);

    n = gluNewQuadric();
    gluQuadricTexture(n, GL_TRUE);
    gluQuadricDrawStyle(n, GLU_FILL);

    t = gluNewQuadric();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(t, GL_TRUE);
    gluQuadricDrawStyle(t, GLU_FILL);

    jp = gluNewQuadric();
    gluQuadricTexture(jp, GL_TRUE);
    gluQuadricDrawStyle(jp, GLU_FILL);

    lua = gluNewQuadric();
    gluQuadricTexture(lua, GL_TRUE);
    gluQuadricDrawStyle(lua, GLU_FILL);

    lla = gluNewQuadric();
    gluQuadricTexture(lla, GL_TRUE);
    gluQuadricDrawStyle(lla, GLU_FILL);

    lhnd = gluNewQuadric();
    gluQuadricTexture(lhnd, GL_TRUE);
    gluQuadricDrawStyle(lhnd, GLU_FILL);

    rhnd = gluNewQuadric();
    gluQuadricTexture(rhnd, GL_TRUE);
    gluQuadricDrawStyle(rhnd, GLU_FILL);

    rft = gluNewQuadric();
    gluQuadricTexture(rft, GL_TRUE);
    gluQuadricDrawStyle(rft, GLU_FILL);

    lft = gluNewQuadric();
    gluQuadricTexture(lft, GL_TRUE);
    gluQuadricDrawStyle(lft, GLU_FILL);

    rua = gluNewQuadric();
    gluQuadricTexture(rua, GL_TRUE);
    gluQuadricDrawStyle(rua, GLU_FILL);

    rla = gluNewQuadric();
    gluQuadricTexture(rla, GL_TRUE);
    gluQuadricDrawStyle(rla, GLU_FILL);

    lul = gluNewQuadric();
    gluQuadricTexture(lul, GL_TRUE);
    gluQuadricDrawStyle(lul, GLU_FILL);

    lll = gluNewQuadric();
    gluQuadricTexture(lll, GL_TRUE);
    gluQuadricDrawStyle(lll, GLU_FILL);

    rul = gluNewQuadric();
    gluQuadricTexture(rul, GL_TRUE);
    gluQuadricDrawStyle(rul, GLU_FILL);

    rll = gluNewQuadric();
    gluQuadricTexture(rll, GL_TRUE);
    gluQuadricDrawStyle(rll, GLU_FILL);
}

