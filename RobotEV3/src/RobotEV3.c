#include <ev3.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

char current_speed = 20;
int optimal = 20;
int current_time = 0, search_interval = 15, wander_search_interval = 300;

void turn_right(int amount){
	OnFwdReg(OUT_B, (char)(current_speed + amount));
	OnFwdReg(OUT_C, (char)(current_speed));
	usleep(10000);
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
}

void turn_left(int amount){
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed + amount);
	usleep(10000);
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
}

void turn_left_high(int amount){
	OnRevReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed + amount);
	usleep(10000);
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
}

void turn_right_high(int amount){
	OnFwdReg(OUT_B, (char)(current_speed + amount));
	OnFwdReg(OUT_C, (char)(0));
	usleep(10000);
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
}

void wall_follow(){
	int ref_sensor = ReadSensor(IN_3);
	int difference = (optimal - ref_sensor) * 2;
	if(difference > 9){
		OnRevReg(OUT_B, (char)(current_speed));
		OnRevReg(OUT_C, (char)(current_speed));
		usleep(40000);
		OnFwdReg(OUT_B, (char)current_speed);
		OnFwdReg(OUT_C, (char)current_speed);
		turn_right_high(difference);
	}else if(difference < -15){
		turn_left_high(-difference);
	}
	else if(difference < 0){
		turn_left(-difference);
	}else if(difference > 0){
		turn_right(difference);
	}
}

void wander(){
	ResetRotationCount(OUT_B);
	OnFwdReg(OUT_B, (char)current_speed);
	OnRevReg(OUT_C, (char)current_speed);
	while(MotorRotationCount(OUT_B) < 180);
	OnRevReg(OUT_B, current_speed);
	OnRevReg(OUT_C, current_speed);
	usleep(600000);
	OnFwdReg(OUT_B, current_speed/2);
	OnFwdReg(OUT_C, current_speed/2);
	while(ReadSensor(IN_3) > 10);
}

bool look_for_can(int search_distance){
	ResetRotationCount(OUT_B);
	OnFwdReg(OUT_B, (char)10);
	OnRevReg(OUT_C, (char)10);
	while(MotorRotationCount(OUT_B) < 720){
		int heading = ReadSensor(IN_1);
		if(heading < search_distance){
			ResetRotationCount(OUT_B);
			while(ReadSensor(IN_1) < search_distance);
			int final_count = MotorRotationCount(OUT_B);
			OnFwdReg(OUT_C, (char)10);
			OnRevReg(OUT_B, (char)10);
			while(MotorRotationCount(OUT_B) > ((final_count) / 2));
			OnRevReg(OUT_B, current_speed);
			OnRevReg(OUT_C, current_speed);
			usleep(600000);
			OnFwdReg(OUT_B, current_speed/2);
			OnFwdReg(OUT_C, current_speed/2);
			return true;
		}
	}
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
	return false;
}

void goal_find(){
	SetAllSensorMode(US_DIST_MM, NO_SEN, COL_COLOR, NO_SEN);
	while(true){
		int color_sensor = ReadSensor(IN_3);
		if(color_sensor == 2){
			SetAllSensorMode(US_DIST_MM, NO_SEN, COL_REFLECT, NO_SEN);
			break;
		}else if(color_sensor == 5){
			Off(OUT_B);
			Off(OUT_C);
			PlayTone(TONE_C2, NOTE_WHOLE);
			usleep(1000000);
			ResetRotationCount(OUT_B);
			OnFwdReg(OUT_B, (char)10);
			OnRevReg(OUT_C, (char)10);
			while(MotorRotationCount(OUT_B) < 360);
			look_for_can(230);
			ResetRotationCount(OUT_B);
			while(MotorRotationCount(OUT_B) < 1000);
			exit(0);
		}
	}
}

int main(void)
{
	ButtonWaitForPress(BTNCENTER);
	SetAllSensorMode(US_DIST_MM, NO_SEN, COL_REFLECT, NO_SEN);
	time_t start, wander_start;
	OnFwdReg(OUT_B, current_speed);
	OnFwdReg(OUT_C, current_speed);
	while(ReadSensor(IN_3) > 10);
	start = time(NULL);
	wander_start = time(NULL);
	while(1){
		wall_follow();
		int search_time_passed = time(NULL) - start;
		int wander_time_passed = time(NULL) - wander_start;
		if(search_time_passed >= search_interval){
			if(look_for_can(1000)){
				goal_find();
			}
			start = time(NULL);
			wander_start = time(NULL);
		}else if(wander_time_passed >= wander_search_interval){
			wander();
			start = time(NULL);
			wander_start = time(NULL);
		}
	}
	return 0;
}
