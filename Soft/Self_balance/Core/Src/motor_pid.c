/*
 * motor_pid.c
 *
 *  Created on: Feb 15, 2022
 *      Author: michu
 */

#include "motor_pid.h"

void pid_init(motor_pid* pid, float Kp, float Ki, float Kd, int anti_windup){

	pid->prev_error = 0;
	pid->total_error = 0;

	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;

	pid->anti_windup_limit = anti_windup;

}

void pid_reset(motor_pid* pid){

	pid->prev_error = 0;
	pid->total_error = 0;
}

int pid_calculate(motor_pid* pid, int set_point, int process_var){

	int error;
	float p_term, i_term, d_term;

	// calculate error, update total error
	error = set_point - process_var;
	pid->total_error += error;

	// calculate P-term
	p_term = (float)(error * pid->Kp);

	// calculate I-term
	i_term = (float)(pid->total_error * pid->Ki);

	// calculate D-term
	d_term = (float)(pid->Kd * (error - pid->prev_error));

	// correct total error, update previous error
	if(i_term >= pid->anti_windup_limit)
		i_term = pid->anti_windup_limit;
	else if(i_term <= -pid->anti_windup_limit)
		i_term = -pid->anti_windup_limit;

	pid->prev_error = error;

	return (int) (p_term + i_term + d_term);
}
