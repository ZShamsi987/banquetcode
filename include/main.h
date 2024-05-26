#ifndef MAIN_H
#define MAIN_H

#include "vex.h"

extern vex::motor leftMotor1;
extern vex::motor leftMotor2;
extern vex::motor leftMotor3;
extern vex::motor rightMotor1;
extern vex::motor rightMotor2;
extern vex::motor rightMotor3;

extern vex::motor intakeMotor;

extern vex::motor cataMotor;

extern vex::controller Controller1;

void userControl(void);
void autonomous(void);

#endif
