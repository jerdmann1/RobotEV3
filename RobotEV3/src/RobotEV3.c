#include <ev3.h>
#include <math.h>
#include <stdbool.h>

#define FULL_TURN 1100
#define WHEEL_DIAMETER 5.6 /* number of obstacles */
#define MAX_OBSTACLES 25 /* maximum number of obstacles */

typedef struct {
    int x;
    int y;
} Element;

int num_obstacles = 13;

double obstacle[MAX_OBSTACLES][2] = /* obstacle locations */
{{0.61, 2.743},{0.915, 2.743},{1.219, 2.743},{1.829, 1.219},
{1.829, 1.524},{ 1.829, 1.829}, {1.829, 2.134},{2.743, 0.305},
{2.743, 0.61},{2.743, 0.915},{2.743, 2.743},{3.048, 2.743},
{3.353, 2.743}};

double start[2] = {0.305, 1.219}; /* start location */

double goal[2] = {3.658, 1.829}; /* goal location */

bool is_unseen(char c){
    return c == '_';
}

int roundNo(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}

void print_room(char room[17][11]){
	int i = 0, j = 0;
    printf("\x1b[2J");
    for(i = 0; i < 17; i++){
        for(j = 0; j < 11; j++){
            if(room[i][j] == 0){
                printf("%5c", 'G');
            }
            else if(room[i][j] != 'X' && room[i][j] != 'S' && room[i][j] != '_'){
                printf("%5d", room[i][j] - '0');
            }else{
                printf("%5c", room[i][j]);
            }
        }
        printf("\n");
    }
}

void bfs(char room[17][11], int goal[2]){
    Element q[1600];
    int cnt = 0, orig_cnt = 0, prev_orig_cnt = 0, step = 1, u = 0;
    Element temp = {goal[0], goal[1]};
    q[orig_cnt++] = temp;
    while((orig_cnt - prev_orig_cnt) > 0){
    	int i;
        for(i = prev_orig_cnt; i < orig_cnt; i++){
            if(q[i].x - 1 >= 0){
                if(is_unseen(room[q[i].x - 1][q[i].y])){
                    room[q[i].x - 1][q[i].y] = step + '0';
                    Element temp = {q[i].x - 1, q[i].y};
                    q[orig_cnt + cnt++] = temp;
                    u++;
                }
            }
            if(q[i].x + 1 < 16){
                if(is_unseen(room[q[i].x + 1][q[i].y])){
                    room[q[i].x + 1][q[i].y] = step + '0';
                    Element temp = {q[i].x + 1, q[i].y};
                    q[orig_cnt + cnt++] = temp;
                    u++;
                }
            }
            if(q[i].y - 1 >= 0){
                if(is_unseen(room[q[i].x][q[i].y - 1])){
                    room[q[i].x][q[i].y - 1] = step + '0';
                    Element temp = {q[i].x, q[i].y - 1};
                    q[orig_cnt + cnt++] = temp;
                    u++;
                }
            }
            if(q[i].y + 1 < 10){
                if(is_unseen(room[q[i].x][q[i].y + 1])){
                    room[q[i].x][q[i].y + 1] = step + '0';
                    Element temp = {q[i].x, q[i].y + 1};
                    q[orig_cnt + cnt++] = temp;
                    u++;
                }
            }
        }
        step++;
        cnt = 0;
        prev_orig_cnt = orig_cnt;
        orig_cnt += u;
        u = 0;
    }
}

void get_commands(int commands[50], char room[17][11], int goal[2], int start[2]){
    int curr[2] = {start[0], start[1]};
    int i = 0, orientation = 1;
    while(goal[0] != curr[0] || goal[1] != curr[1]){
        int min = INT_MAX;
        int best_pos[2];
        int comm = 0;
        if(curr[0] - 1 >= 0){
            if(room[curr[0]-1][curr[1]] != 'X'){
                if(room[curr[0]-1][curr[1]] < min){
                    min = room[curr[0]-1][curr[1]];
                    best_pos[0] = curr[0]-1;
                    best_pos[1] = curr[1];
                    comm = -1;
                }
            }
        }
        if(curr[0] + 1 < 17){
            if(room[curr[0]+1][curr[1]] != 'X'){
                if(room[curr[0]+1][curr[1]] < min){
                    min = room[curr[0]+1][curr[1]];
                    best_pos[0] = curr[0]+1;
                    best_pos[1] = curr[1];
                    comm = 1;
                }
            }
        }
        if(curr[1] - 1 >= 0){
            if(room[curr[0]][curr[1]-1] != 'X'){
                if(room[curr[0]][curr[1]-1] < min){
                    min = room[curr[0]][curr[1]-1];
                    best_pos[0] = curr[0];
                    best_pos[1] = curr[1]-1;
                    comm = 2;
                }
            }
        }
        if(curr[1] + 1 < 11){
            if(room[curr[0]][curr[1]+1] != 'X'){
                if(room[curr[0]][curr[1]+1] < min){
                    min = room[curr[0]][curr[1]+1];
                    best_pos[0] = curr[0];
                    best_pos[1] = curr[1]+1;
                    comm = -2;
                }
            }
        }
        curr[0] = best_pos[0];
        curr[1] = best_pos[1];
        if(comm != orientation){
            if(comm == 2 && orientation == 1){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 2;
            }else if(comm == 1 && orientation == 2){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = 1;
            }else if(comm == 1 && orientation == -2){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 1;
            }else if(comm == -2 && orientation == 1){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = -2;
            }else if(comm == -2 && orientation == -1){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -2;
            }else if(comm == 2 && orientation == -1){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = 2;
            }else if(comm == -1 && orientation == 2){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -1;
            }else if(comm == -1 && orientation == -2){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = -1;
            }else if(comm == -1 && orientation == 1){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -1;
            }else if(comm == 1 && orientation == -1){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 1;
            }else if(comm == 2 && orientation == -2){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 2;
            }else if(comm == -2 && orientation == 2){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -2;
            }
        }else{
            commands[i++] = 1;
        }
    }
}

bool check_box(int i, int j){
	int k;
    for(k = 0; k < num_obstacles; k++){
        if((roundNo(obstacle[k][0] / 0.305) == i) && (roundNo(obstacle[k][1] / 0.305) == j)){
            return true;
        }
    }
    return false;
}

bool turn_right(double angle){
	double circumference = ((22.6 * M_PI) * (angle/360)) / 1.26;
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
	double circumference = ((22.6 * M_PI) * (angle/360)) / 1.26;
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
	char room[17][11];
	int commands[50];
	int i, j;
	for(i = 0; i < 50; i++){
		commands[i] = 0;
	}
	for(i = 0; i < 17; i++){
		for(j = 0; j < 11; j++){
			if(roundNo(start[0] / 0.305) == i && roundNo(start[1] / 0.305) == j){
				room[i][j] = 'S';
			}else if(roundNo(goal[0] / 0.305) == i && roundNo(goal[1] / 0.305) == j){
				room[i][j] = 0;
			}
			else if(check_box(i, j)){
				room[i][j] = 'X';
			}else{
				room[i][j] = '_';
			}
		}
	}
	int goal_cords[2] = {roundNo(goal[0] / 0.305), roundNo(goal[1] / 0.305)};
	int start_cords[2] = {roundNo(start[0] / 0.305), roundNo(start[1] / 0.305)};
	bfs(room, goal_cords);
	get_commands(commands, room, goal_cords, start_cords);
	ButtonWaitForPress(BTNCENTER);
	i = 0;
	while(commands[i] != 0){
		if(commands[i] == 1){
			forward(30.5);
		}else if(commands[i] == 2){
			turn_right(90);
		}else if(commands[i] == -2){
			turn_left(90);
		}
		i++;
	}
	return 0;
}
