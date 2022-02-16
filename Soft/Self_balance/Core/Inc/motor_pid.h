/*
 * motor_pid.h
 *
 *  Created on: Feb 15, 2022
 *      Author: michu
 */

#ifndef INC_MOTOR_PID_H_
#define INC_MOTOR_PID_H_

typedef struct{

	int prev_error;
	int total_error;

	float Kp;
	float Ki;
	float Kd;

	int anti_windup_limit;
}motor_pid;

void pid_init(motor_pid*, float, float, float, int);
void pid_reset(motor_pid*);
int pid_calculate(motor_pid*, int, int);

#endif /* INC_MOTOR_PID_H_ */
