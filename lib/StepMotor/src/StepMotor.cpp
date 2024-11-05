#include <Arduino.h>
#include <StepMotor.h>
#include <AccelStepper.h>

StepMotor::StepMotor(int step_pin, int direction_pin, int ms1_pin, int ms2_pin, int reset_pin, int enable_pin, int steps_per_degree, int min_limit, int max_limit) {
    StepMotor::step_pin = step_pin;
    StepMotor::direction_pin = direction_pin;
    StepMotor::ms1_pin = ms1_pin;
    StepMotor::ms2_pin = ms2_pin;
    StepMotor::reset_pin = reset_pin;
    StepMotor::enable_pin = enable_pin;
    StepMotor::steps_per_degree = steps_per_degree;
    StepMotor::min_limit = min_limit;
    StepMotor::max_limit = max_limit;
    
    pinMode(StepMotor::ms1_pin, OUTPUT);
    pinMode(StepMotor::ms2_pin, OUTPUT);
    pinMode(StepMotor::reset_pin, OUTPUT);
    pinMode(StepMotor::enable_pin, OUTPUT);

    StepMotor::controller = new AccelStepper(AccelStepper::DRIVER, StepMotor::step_pin, StepMotor::direction_pin);
}

void StepMotor::set_direction_values(String direction_values[2]){
    for(int i = 0; i < 2;i++){
        StepMotor::direction_values[i] = direction_values[i];
    }
}

int StepMotor::get_direction_index(String direction){
    for(int i = 0; i < 2;i++){
        if(StepMotor::direction_values[i].indexOf(direction) != -1){
            return i;
        }
    }

    return -1;
}

void StepMotor::move(int degrees, String direction, bool run_now) {
    int target_steps = StepMotor::steps_per_degree * degrees;
    int direction_index = StepMotor::get_direction_index(direction);
    int requested_position = 0;

    if(direction_index == -1){
        Serial.println("Invalid direction");
        return;
    }

    if(StepMotor::direction_values[direction_index].indexOf("+") != -1){
        requested_position = StepMotor::controller->currentPosition() + target_steps;
    }else if (StepMotor::direction_values[direction_index].indexOf("-") != -1){
        requested_position = StepMotor::controller->currentPosition() - target_steps;
    }


    if(requested_position <= StepMotor::max_limit && requested_position >= StepMotor::min_limit){
        StepMotor::controller->moveTo(requested_position);
        if(run_now){
            StepMotor::controller->run();
        }
    }else {
        Serial.println("Invalid degree value");
    }
}

void StepMotor::set_microstepping(bool ms1, bool ms2){
    if(ms1){
        digitalWrite(StepMotor::ms1_pin, HIGH);
        Serial.println("Microstepping MS1: HIGH");
    }else {
        digitalWrite(StepMotor::ms1_pin, LOW);
        Serial.println("Microstepping MS1: LOW");
    }

    if(ms2){
        digitalWrite(StepMotor::ms2_pin, HIGH);
        Serial.println("Microstepping MS2: HIGH");
    }else {
        digitalWrite(StepMotor::ms2_pin, LOW);
        Serial.println("Microstepping MS2: LOW");
    }
}

void StepMotor::power(String state){
    state.toUpperCase();
    if(state == "ON"){
        digitalWrite(StepMotor::reset_pin, HIGH);
        Serial.println("Motor ON");
    }else if(state == "OFF") {
        digitalWrite(StepMotor::reset_pin, LOW);
        Serial.println("Motor OFF");
    }else {
        Serial.println("Power state not valid");
    }
}
