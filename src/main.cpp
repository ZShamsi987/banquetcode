#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_mtr1(2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor left_mtr2(3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor left_mtr3(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_mtr1(9, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_mtr2(8, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor right_mtr3(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor intake_mtr(10, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor cata_mtr(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut wings('A');

void initialize() {
    // blank
}

void disabled() {
    // blank
}

void competition_initialize() {
    // blank
}

void autonomous() {
    // blank
}

void opcontrol() {
    bool cataOn = false;
	bool PistonOn=false;

    while (true) {
        int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        int left_power = forward + turn;
        int right_power = forward - turn;

        left_mtr1.move(left_power);
        left_mtr2.move(left_power);
        left_mtr3.move(left_power);
        right_mtr1.move(right_power);
        right_mtr2.move(right_power);
        right_mtr3.move(right_power);

		//intake
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake_mtr.move(127);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake_mtr.move(-127);
        } else {
            intake_mtr.move(0);
        }

        // Cata
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            cataOn = !cataOn;

        }

        if(cataOn){
            cata_mtr.move(127);
        }
        else{
            cata_mtr.move(0);
        }

        // Wings
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            PistonOn = !PistonOn;
        }

		wings.set_value(PistonOn);
		

        pros::delay(20);
    }
}
