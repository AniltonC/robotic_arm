#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include "Arduino.h"

class StepMotor{
    private:
        int convert_speed(String speed);
    public:
        int step_pin;
        int direction_pin;
        int ms1_pin;
        int ms2_pin;
        int reset_pin;
        int enable_pin;
        int steps_per_revolution;

        StepMotor(int step_pin, int direction_pin, int ms1_pin, int ms2_pin, int reset_pin, int enable_pin);

        void move(int degrees, String direction, String speed);
        void set_microstepping(bool ms1, bool ms2);
        void power(String state);
};

#endif