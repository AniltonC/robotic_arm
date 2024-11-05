#include <Arduino.h>
#include <StepMotor.h>
#include <Arm.h>

Arm::Arm(StepMotor* joints_array[], int number_of_motors){
    Arm::number_of_motors = number_of_motors;
    for(int i = 0;i < number_of_motors;i++){
        Arm::joints[i] = joints_array[i];
    }
}

void Arm::set_move_joints(int motor_angles[]){
    for(int i = 0;i < Arm::number_of_motors;i++){
        Arm::joints[i]->controller->moveTo(motor_angles[i]);
    }
}

void Arm::set_joints_max_speed(double max_speed){
    for(int i = 0;i < Arm::number_of_motors;i++){
        Arm::joints[i]->controller->setMaxSpeed(max_speed);
    }
}

void Arm::set_joints_acceleration(double acceleration){
    for(int i = 0;i < Arm::number_of_motors;i++){
        Arm::joints[i]->controller->setAcceleration(acceleration);
    }
}

void Arm::execute_run_joints(){
    for(int i = 0;i < Arm::number_of_motors;i++){
        Arm::joints[i]->controller->run();
    }
}

void Arm::power_motors(String state){
    if(state == "ON"){
        for(int i = 0;i < Arm::number_of_motors;i++){
            Arm::joints[i]->power("ON");
        }
    }else if(state == "OFF"){
        for(int i = 0;i < Arm::number_of_motors;i++){
            Arm::joints[i]->power("OFF");
        }
    }
}