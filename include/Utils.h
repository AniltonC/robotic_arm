#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>

void bind_to_array(String command, int motor_angles[5]){
	int start_index = 1;
	int end_index;
	int index = 0;

	while((end_index = command.indexOf(',', start_index)) > 0 && index < 5) {
		motor_angles[index++] = command.substring(start_index, end_index).toInt();
		start_index = end_index + 1;
	}

	if(index < 5){
		end_index = command.indexOf(']', start_index);
		motor_angles[index] = command.substring(start_index, end_index).toInt();
	}
}


#endif