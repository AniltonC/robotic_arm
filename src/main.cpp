#include <Arduino.h>
#include <StepMotor.h>
#include <AccelStepper.h>

#define BASE_STEP 30
#define BASE_DIRECTION 32
#define BASE_MS1 36
#define BASE_MS2 38
#define BASE_RESET 40

StepMotor base(BASE_STEP, BASE_DIRECTION, BASE_MS1, BASE_MS2, BASE_RESET, 0);
//AccelStepper stepper1(1, 30, 32);

void setup() {
	Serial.begin(9600);
	base.power("ON");
	base.set_microstepping(false, false);

	//stepper1.setMaxSpeed(200);
	//stepper1.setAcceleration(100);
	Serial.println("Type angle and direction to move base motor");
	Serial.println("Ex: 90,clockwise");
}

void loop() {
	if(Serial.available() > 0){
		String command = Serial.readStringUntil('\n');
		int comma_index = command.indexOf(',');
		if(comma_index != -1){
			String degree = command.substring(0, comma_index);
			String direct = command.substring(comma_index + 1);
			//stepper1.moveTo(degree.toInt());
			//stepper1.run();
			base.move(degree.toInt(), direct, "default");
		}else {
			Serial.println("Invalid command");
		}
	}
}
