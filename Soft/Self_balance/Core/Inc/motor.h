/*
 * encoder.h
 *
 *  Created on: Feb 15, 2022
 *      Author: michu
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "motor_pid.h"
#include "max14870.h"

#define MOTOR_KP 100 // wzmocnienie krytyczne około 9
#define MOTOR_KI 1// okres 0.15sec
#define MOTOR_KD 0
#define ANTI_WINDUP 3000


#define ENCODER_RESOLUTION 48
#define MOTOR_GEAR 20.4

#define TIMER_FREQUENCY 50
#define SECOND_IN_MINUTE 60


// structure for motor handles
typedef struct{
	TIM_HandleTypeDef * ENC_timer;

	uint16_t resolution;

	uint8_t mode;

	int pulse_count;
	int measured_speed;
	int set_speed;

	int measured_position;
	int set_position;

	int PWM_value;

	motor_pid pid_controller;
	max14870 motor_board;
}motor_str;

typedef enum{
	SPEED,
	POS
}motor_modes;

void motor_init(motor_str*, TIM_HandleTypeDef*);
void motor_choose_mode(motor_str*, uint8_t);
void motor_calculate_speed(motor_str*);
void motor_calculate_position(motor_str*);
void motor_reset_position(motor_str*);
void motor_update_count(motor_str*);
void motor_set_speed(motor_str*,int);
void motor_set_position(motor_str*,int);
#endif /* INC_MOTOR_H_ */
