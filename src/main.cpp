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

pros::Motor_Group left({left_mtr1, left_mtr2, left_mtr3});
pros::Motor_Group right({right_mtr1, right_mtr2, right_mtr3});

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
    left.move_velocity(200);
	right.move_velocity(200);
	pros::delay(1000);
	left.move_velocity(0);
	right.move_velocity(0);
}

void opcontrol() {
    bool cataOn = false;
	bool PistonOn=false;

    while (true) {
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // // Get analog stick values
        // int forward_left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // int forward_right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // int turn_left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        // int turn_right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // // Calculate the average forward and turn values
        // int forward = (forward_left + forward_right) / 2;
        // int turn = (turn_left + turn_right) / 2;

		int left_power = power + turn;
		int right_power = power - turn;

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
