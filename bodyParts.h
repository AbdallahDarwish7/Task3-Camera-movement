//
// Created by abdallahdarwesh on 3/25/20.
//

#ifndef HUMMAN_BODY_BODYPARTS_H
#define HUMMAN_BODY_BODYPARTS_H

#include <GL/glut.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define TORSO_HEIGHT 5.0
#define TORSO_RADIUS 1.3
#define UPPER_ARM_HEIGHT 2.5
#define LOWER_ARM_HEIGHT 2.3
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define FINGER_RADIUS 0.1
#define FINGER_HEIGHT 0.3
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 3.1
#define UPPER_LEG_HEIGHT 3.3
#define HEAD_HEIGHT 1.2
#define HEAD_RADIUS 1.4
#define FOOT_RADIUS 0.7
#define FOOT_HEIGHT 1.1
#define NECK_RADIUS 0.5
#define NECK_HEIGHT 1.0
#define JOINT_POINT_RADIUS 0.5
#define JOINT_POINT_HEIGHT 0.5

void head();

void neck();

void torso();

void joint_point();

void finger_joint(GLfloat x , GLfloat y, GLfloat z);

void left_upper_arm();

void left_lower_arm();

void upper_finger();

void lower_finger();

//void finger(GLfloat x , GLfloat y, GLfloat z);

void thumb(GLfloat x , GLfloat y, GLfloat z);

void hand();

void right_upper_arm() ;

void right_lower_arm() ;

void left_upper_leg() ;

void left_lower_leg();

void left_foot() ;

void right_upper_leg() ;

void right_lower_leg() ;

void right_foot() ;


void fill_objects();

#endif //HUMMAN_BODY_BODYPARTS_H
