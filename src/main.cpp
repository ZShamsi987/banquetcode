#include "main.h"

vex::motor leftMotor1(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor leftMotor2(vex::PORT9, vex::gearSetting::ratio18_1, false);
vex::motor leftMotor3(vex::PORT8, vex::gearSetting::ratio18_1, false);
vex::motor rightMotor1(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor rightMotor2(vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor rightMotor3(vex::PORT3, vex::gearSetting::ratio18_1, true);

vex::motor intakeMotor(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor cataMotor(vex::PORT6, vex::gearSetting::ratio36_1, false);

vex::controller Controller1;

void userControl(void) {
    while (true) {
        int forward = Controller1.Axis2.position();
        int turn = Controller1.Axis4.position();
        
        leftMotor1.spin(vex::directionType::fwd, forward + turn, vex::velocityUnits::pct);
        leftMotor2.spin(vex::directionType::fwd, forward + turn, vex::velocityUnits::pct);
        leftMotor3.spin(vex::directionType::fwd, forward + turn, vex::velocityUnits::pct);
        
        rightMotor1.spin(vex::directionType::fwd, forward - turn, vex::velocityUnits::pct);
        rightMotor2.spin(vex::directionType::fwd, forward - turn, vex::velocityUnits::pct);
        rightMotor3.spin(vex::directionType::fwd, forward - turn, vex::velocityUnits::pct);
        
        if (Controller1.ButtonL1.pressing()) {
            intakeMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        } else if (Controller1.ButtonL2.pressing()) {
            intakeMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        } else {
            intakeMotor.stop();
        }

        if (Controller1.ButtonA.pressing()) {
            cataMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        } else {
            cataMotor.stop();
        }
        
        vex::task::sleep(20);
    }
}

//(to be defined)
void autonomous(void) {
    // Placeholder 
}

int main() {
    vexcodeInit();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(userControl);
    
    while (true) {
        vex::task::sleep(100);
    }
}
