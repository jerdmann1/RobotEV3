#include <ev3.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

char current_speed = 20;
int optimal = 20;
int current_time = 0, search_interval = 5;

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

bool wander(){
	int ref_sensor = ReadSensor(IN_3);
	if(ref_sensor <= optimal){
		OnRevReg(OUT_B, (char)20);
		OnRevReg(OUT_C, (char)20);
		usleep(500000);
		OnFwdReg(OUT_B, (char)20);
		OnRevReg(OUT_C, (char)20);
		usleep(1500000);
		OnFwdReg(OUT_B, current_speed);
		OnFwdReg(OUT_C, current_speed);
		return true;
	}
	return false;
}

void look_for_can(){
	ResetRotationCount(OUT_B);
	OnFwdReg(OUT_B, (char)10);
	OnRevReg(OUT_C, (char)10);
	while(MotorRotationCount(OUT_B) < 720){
		if(ReadSensor(IN_1) < 250){
			OnFwdReg(OUT_B, current_speed);
			OnFwdReg(OUT_C, current_speed);
			return;
		}
	}
	OnFwdReg(OUT_B, (char)current_speed);
	OnFwdReg(OUT_C, (char)current_speed);
}

int main(void)
{
	ButtonWaitForPress(BTNCENTER);
	SetAllSensorMode(US_DIST_MM, NO_SEN, COL_REFLECT, NO_SEN);
	time_t start;
	bool follow = false;
	OnFwdReg(OUT_B, current_speed);
	OnFwdReg(OUT_C, current_speed);
	start = time(NULL);
	while(1){
		if(follow){
			wall_follow();
		}else if(wander()){
			start = time(NULL);
		}
		int time_passed = time(NULL) - start;
		if(time_passed >= search_interval){
			look_for_can();
			start = time(NULL) + 3;
		}
	}
	return 0;
}
