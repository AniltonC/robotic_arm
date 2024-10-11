#include <Arduino.h>
#include <StepMotor.h>

StepMotor::StepMotor(int step_pin, int direction_pin, int ms1_pin, int ms2_pin, int reset_pin, int enable_pin) {
    StepMotor::step_pin = step_pin;
    StepMotor::direction_pin = direction_pin;
    StepMotor::ms1_pin = ms1_pin;
    StepMotor::ms2_pin = ms2_pin;
    StepMotor::reset_pin = reset_pin;
    StepMotor::enable_pin = enable_pin;
    StepMotor::steps_per_revolution = 0;
    
    pinMode(StepMotor::step_pin, OUTPUT);
    pinMode(StepMotor::direction_pin, OUTPUT);
    pinMode(StepMotor::ms1_pin, OUTPUT);
    pinMode(StepMotor::ms2_pin, OUTPUT);
    pinMode(StepMotor::reset_pin, OUTPUT);
    pinMode(StepMotor::enable_pin, OUTPUT);
}

int StepMotor::convert_speed(String speed){
    if(speed == "slow"){
        return 4000;
    }else if(speed == "default"){
        return 800;
    }else if(speed == "fast"){
        return 600;
    }else {
        Serial.println("Invalid speed");
        return -1;
    }
}

void StepMotor::move(int degrees, String direction, String speed) {
    if(StepMotor::steps_per_revolution !=0){
        if(direction == "clockwise"){
            digitalWrite(StepMotor::direction_pin, HIGH);
        }else if (direction == "anticlockwise"){
            digitalWrite(StepMotor::direction_pin, LOW);
        }else {
            Serial.println("Invalid direction");
        }

        int steps = (degrees / 360.0) * steps_per_revolution;

        Serial.print("Moving ");
        Serial.print(degrees);
        Serial.print(" ");
        Serial.println(direction);
        for(int counter = 0; counter < steps; counter++){
            digitalWrite(StepMotor::step_pin, HIGH);
            delayMicroseconds(convert_speed(speed));
            digitalWrite(StepMotor::step_pin, LOW);
            delayMicroseconds(convert_speed(speed));
        }
        Serial.println("Movement finished");
    }else {
        Serial.println("MS1 and MS2 value need to be setted");
    }
}

void StepMotor::set_microstepping(bool ms1, bool ms2){
    if(ms1){
        digitalWrite(StepMotor::ms1_pin, HIGH);
    }else {
        digitalWrite(StepMotor::ms1_pin, LOW);
    }

    if(ms2){
        digitalWrite(StepMotor::ms2_pin, HIGH);
    }else {
        digitalWrite(StepMotor::ms2_pin, LOW);
    }

    if(!ms1 && !ms2){
        StepMotor::steps_per_revolution = 400;
    }else if(ms1 && ms2){
        StepMotor::steps_per_revolution = 3200;
    }
}

void StepMotor::power(String state){
    state.toUpperCase();
    if(state == "ON"){
        digitalWrite(StepMotor::reset_pin, HIGH);
    }else if(state == "OFF") {
        digitalWrite(StepMotor::reset_pin, LOW);
    }else {
        Serial.println("Power state not valid");
    }
}
