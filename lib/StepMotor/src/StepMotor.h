#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include <AccelStepper.h>
#include "Arduino.h"

class StepMotor{
    private:
        int get_direction_index(String direction);
    public:
        int step_pin;
        int direction_pin;
        int ms1_pin;
        int ms2_pin;
        int reset_pin;
        int enable_pin;
        int steps_per_degree;
        int min_limit;
        int max_limit;
        String direction_values[2];
        AccelStepper* controller;

        StepMotor(int step_pin, int direction_pin, int ms1_pin, int ms2_pin, int reset_pin, int enable_pin, int steps_per_degree, int min_limit, int max_limit);

        void move(int degrees, String direction, bool run_now);
        void set_direction_values(String direction_values[2]);
        void set_microstepping(bool ms1, bool ms2);
        void power(String state);
};

#endif