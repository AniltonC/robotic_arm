#ifndef ARM_H
#define ARM_H

#include <StepMotor.h>
#include "Arduino.h"

class Arm{
    public:
        StepMotor* joints[5];
        int number_of_motors;

        Arm(StepMotor* joints_array[], int number_of_motors);

        void set_move_joints(int motor_angles[]);
        void set_joints_max_speed(double max_speed);
        void set_joints_acceleration(double max_acceleration);
        void execute_run_joints();
        void power_motors(String state);

        
};

#endif