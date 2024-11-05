#include <Arduino.h>
#include <StepMotor.h>
#include <MotorParams.h>
#include <Arm.h>
#include <Utils.h>

StepMotor j1_motor(J1_STEP, J1_DIRECTION, J1_MS1, J1_MS2, J1_RESET, 0, 180, -16200, 21600);
StepMotor j2_motor(J2_STEP, J2_DIRECTION, J2_MS1, J2_MS2, J2_RESET, 0, 180, -16200, 21600);
StepMotor j3_motor(J3_STEP, J3_DIRECTION, J3_MS1, J3_MS2, J3_RESET, 0, 180, -16200, 21600);
StepMotor j4_motor(J4_STEP, J4_DIRECTION, J4_MS1, J4_MS2, J4_RESET, 0, 180, -16200, 21600);
StepMotor j5_motor(J5_STEP, J5_DIRECTION, J5_MS1, J5_MS2, J5_RESET, 0, 180, -16200, 21600);

int motor_angles[5];
int motor_target;
StepMotor* joints[] = {&j1_motor, &j2_motor, &j3_motor, &j4_motor, &j5_motor};
Arm robotic_arm(joints, 5);

void setup() {
	Serial.begin(9600);
	robotic_arm.power_motors("ON");
	Serial.println("Ok");

	robotic_arm.joints[0]->set_microstepping(true, true);
	robotic_arm.joints[1]->set_microstepping(true, true);
	robotic_arm.joints[2]->set_microstepping(true, true);
	robotic_arm.joints[3]->set_microstepping(true, true);
	robotic_arm.joints[4]->set_microstepping(true, true);
	String j1_direction_values[2] = {"left+", "right-"};
	String j2_direction_values[2] = {"up-", "down+"};
	String j3_direction_values[2] = {"up-", "down+"};
	String j4_direction_values[2] = {"left-", "right+"};
	String j5_direction_values[2] = {"up-", "down+"};
	robotic_arm.joints[0]->set_direction_values(j1_direction_values);
	robotic_arm.joints[1]->set_direction_values(j2_direction_values);
	robotic_arm.joints[2]->set_direction_values(j3_direction_values);
	robotic_arm.joints[3]->set_direction_values(j4_direction_values);
	robotic_arm.joints[4]->set_direction_values(j5_direction_values);
	
	robotic_arm.set_joints_max_speed(7000.0);
	robotic_arm.set_joints_acceleration(3000.0);
}

void loop() {
	if(Serial.available() > 0){
		delay(10);

		String command = Serial.readStringUntil('\n');

		if(command[0] == '[' && command[command.length() - 1] == ']'){
			bind_to_array(command, motor_angles);

			//j1_motor.controller.moveTo(motor_angles[0]);
			robotic_arm.joints[0]->move(motor_angles[0], "right", false);
			robotic_arm.joints[1]->move(motor_angles[0], "up", false);
			robotic_arm.joints[2]->move(motor_angles[0], "up", false);
			robotic_arm.joints[3]->move(motor_angles[0], "right", false);
			robotic_arm.joints[4]->move(motor_angles[0], "up", false);
		}else {
			Serial.println("Invalid format");
		}
	}

	// Run each motor on robotic arm to setted position
	robotic_arm.execute_run_joints();
}