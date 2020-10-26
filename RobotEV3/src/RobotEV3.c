/*
 \file		HWTest.c
 \author	${user}
 \date		${date}
 \brief		Simple Hello World! for the Ev3
*/
#include <ev3.h>
#include <math.h>
#include <stdbool.h>

#define FULL_TURN 1100
#define WHEEL_DIAMETER 5.6

bool turn_right(double angle){
	double circumference = ((22.6 * M_PI) * (angle/360)) / 1.25;
	circumference = circumference / (WHEEL_DIAMETER * M_PI);
	double rotations = circumference * FULL_TURN;
	rotations = rotations - 0.5 - (rotations<0);
	int r = (int)rotations;
	ResetRotationCount(OUT_B);
	OnFwdReg(OUT_B, '1');
	OnRevReg(OUT_C, '1');
	TermPrintf("%s\n", "Turning Right...\n");
	while(MotorRotationCount(OUT_B) < r);
	Off(OUT_B);
	Off(OUT_C);
	return true;
}

bool turn_left(double angle){
	double circumference = ((22.6 * M_PI) * (angle/360)) / 1.25;
	circumference = circumference / (WHEEL_DIAMETER * M_PI);
	double rotations = circumference * FULL_TURN;
	rotations = rotations - 0.5 - (rotations<0);
	int r = (int)rotations;
	ResetRotationCount(OUT_B);
	OnRevReg(OUT_B, '1');
	OnFwdReg(OUT_C, '1');
	TermPrintf("%s\n", "Turning Left...\n");
	while(-MotorRotationCount(OUT_B) < r);
	Off(OUT_B);
	Off(OUT_C);
	return true;
}

double calc_rotations(double length){
	double circumference = WHEEL_DIAMETER * M_PI;
	return length / circumference;
}

bool forward(double distance){
	ResetRotationCount(OUT_B);
	OnRevReg(OUT_B, '1');
	OnRevReg(OUT_C, '1');
	double rotations = calc_rotations(distance) * FULL_TURN;
	rotations = rotations - 0.5 - (rotations<0);
	int r = (int)rotations;
	TermPrintf("%s\n", "Going Straight...\n");
	while(-MotorRotationCount(OUT_B) < r);
	Off(OUT_B);
	Off(OUT_C);
	return true;
}

int main(void)
{
	ButtonWaitForPress(BTNCENTER);

	forward(20);
	turn_right(90);
	forward(20);
	turn_right(90);
	forward(20);
	turn_right(90);
	forward(20);
	turn_left(360);

	ButtonWaitForPress(BTNCENTER);

	return 0;
}
