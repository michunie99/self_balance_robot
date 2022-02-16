/*
 * motor.c
 *
 *  Created on: Feb 15, 2022
 *      Author: michu
 */

#include "motor.h"

// initialize motor structure, start timer
void motor_init(motor_str* motor, TIM_HandleTypeDef* enc_timer){

	// set up encoder
	motor->ENC_timer = enc_timer;
	motor->resolution = ENCODER_RESOLUTION*MOTOR_GEAR;

	// reset internal variables
	motor->pulse_count = 0;
	motor->measured_speed = 0;
	motor->set_speed = 0;
	motor->PWM_value = 0;

	HAL_TIM_Encoder_Start_IT(enc_timer, TIM_CHANNEL_ALL);
}

// update speed based on the pulse count
void motor_calculate_speed(motor_str* motor){

	int output;

	motor_update_count(motor);
	motor->measured_speed = (motor->pulse_count*TIMER_FREQUENCY
			*SECOND_IN_MINUTE) / motor->resolution;

	output = pid_calculate(&(motor->pid_controller),
			motor->set_speed,motor->measured_speed);

	motor->PWM_value = output;

	if(motor->PWM_value >= 0){
		max1470_set_direction(&(motor->motor_board), CW);
		max14870_set_speed(&(motor->motor_board),motor->PWM_value);

	}else if(motor->PWM_value < 0){
		max1470_set_direction(&(motor->motor_board), CCW);
		max14870_set_speed(&(motor->motor_board),-motor->PWM_value);
	}


}

// update motor counter
void motor_update_count(motor_str* motor){

	motor->pulse_count = (int16_t) __HAL_TIM_GET_COUNTER(motor->ENC_timer);
	__HAL_TIM_SET_COUNTER(motor->ENC_timer, 0);
}

// set target speed (too look into looks bad)
void motor_set_speed(motor_str* motor, int set_speed){
	/*if(motor->set_speed != set_speed);
		pid_reset(&(motor->pid_controller));*/

	motor->set_speed = set_speed;
}
