#include <ev3.h>
#include <math.h>
#include <stdbool.h>

#define FULL_TURN 1100
#define WHEEL_DIAMETER 5.6 /* number of obstacles */
#define MAX_OBSTACLES 25 /* maximum number of obstacles */
#define MAX_OBSTACLES 25 /* maximum number of obstacles */
#define NUM_WALLS 54

/*
int num_obstacles = 13;
double obstacle[MAX_OBSTACLES][2] =
{{0.61, 2.743},{0.915, 2.743},{1.219, 2.743},{1.829, 1.219},
{1.829, 1.524},{ 1.829, 1.829}, {1.829, 2.134},{2.743, 0.305},
{2.743, 0.61},{2.743, 0.915},{2.743, 2.743},{3.048, 2.743},
{3.353, 2.743}};

double start[2] = {0.305, 1.219};

double goal[2] = {3.658, 1.829};
*/

/*
int num_obstacles = 13;
double obstacle[MAX_OBSTACLES][2] =
{{0.61, 2.743},{0.915, 2.743},{1.219, 2.743},{1.829, 1.219},
{1.829, 1.524},{ 1.829, 1.829}, {1.829, 2.134},{2.743, 0.305},
{2.743, 0.61},{2.743, 0.915},{2.743, 2.743},{3.048, 2.743},
{3.353, 2.743}};

double goal[2] = {0.305, 1.219};

double start[2] = {3.658, 1.829};
*/

/*
int num_obstacles = 19;

double obstacle[MAX_OBSTACLES][2] =
{{3*0.305,3*0.305},{3*0.305,4*0.305},{3*0.305,5*0.305},{3*0.305,6*0.305},{3*0.305,7*0.305},{7*0.305,5*0.305},
{7*0.305,6*0.305},{7*0.305,7*0.305},{7*0.305,8*0.305},{7*0.305,9*0.305},{7*0.305,9*0.305},{11*0.305,2*0.305},
{11*0.305,0*0.305},{11*0.305,1*0.305},{11*0.305,3*0.305},{11*0.305,4*0.305},{11*0.305,5*0.305},{11*0.305,6*0.305},
{11*0.305,7*0.305}};

double start[2] = {0.305, 5*0.305};

double goal[2] = {15*0.305, 5*0.305};
*/

/*
int num_obstacles = 19;

double obstacle[MAX_OBSTACLES][2] =
{{3*0.305,3*0.305},{3*0.305,4*0.305},{3*0.305,5*0.305},{3*0.305,6*0.305},{3*0.305,7*0.305},{7*0.305,5*0.305},
{7*0.305,6*0.305},{7*0.305,7*0.305},{7*0.305,8*0.305},{7*0.305,9*0.305},{7*0.305,9*0.305},{11*0.305,2*0.305},
{11*0.305,0*0.305},{11*0.305,1*0.305},{11*0.305,3*0.305},{11*0.305,4*0.305},{11*0.305,5*0.305},{11*0.305,6*0.305},
{11*0.305,7*0.305}};

double goal[2] = {0.305, 5*0.305};

double start[2] = {15*0.305, 5*0.305};
*/

/*
int num_obstacles = 12;

double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305}};

double start[2] = {10*0.305, 1*0.305};

double goal[2] = {3*0.305, 9*0.305};
*/

// MASON ADD OBSTACLES

int num_obstacles = 12;
double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},};
double goal[2] = {11*0.305, 1*0.305};
double start[2] = {3*0.305, 8*0.305};


/*
int num_obstacles = 12;
double obstacle[MAX_OBSTACLES][2] =
{{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},{10*0.305, 3*0.305},
{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},{13*0.305, 6*0.305},};
double goal[2] = {11*0.305, 1*0.305};
double start[2] = {15*0.305, 8*0.305};
*/

/*
int num_obstacles = 12;
// This one has start next to goal see what happens.
double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},};
double goal[2] = {3*0.305,8*0.305};
double start[2] = {3*0.305, 9*0.305};
*/

/*
int num_obstacles = 12;
// This one has start next to goal see what happens.
double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},};
double goal[2] = {3*0.305,8*0.305};
double start[2] = {3*0.305, 9*0.305};
*/

/*
int num_obstacles = 12;
double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{4*0.305, 4*0.305},{4*0.305, 5*0.305},{4*0.305, 5*0.305},{4*0.305, 5*0.305},{4*0.305, 5*0.305},
{7*0.305, 6*0.305},{7*0.305, 7*0.305},{7*0.305, 8*0.305},{7*0.305, 9*0.305},{7*0.305, 10*0.305},{7*0.305, 11*0.305},};
double goal[2] = {3*0.305,8*0.305};
double start[2] = {4*0.305, 2*0.305};
*/

/*
int num_obstacles = 25;
double obstacle[MAX_OBSTACLES][2] =
{{3*0.305,2*0.305},{3*0.305,3*0.305},{3*0.305,4*0.305},{3*0.305,5*0.305},{3*0.305,6*0.305},{3*0.305,7*0.305},{3*0.305,8*0.305},{3*0.305,8*0.305},
{7*0.305,2*0.305},{7*0.305,3*0.305},{7*0.305,4*0.305},{7*0.305,5*0.305},{7*0.305,6*0.305},{7*0.305,7*0.305},{7*0.305,8*0.305},{7*0.305,9*0.305},{7*0.305,10*0.305},
{11*0.305,2*0.305},{11*0.305,0*0.305},{11*0.305,1*0.305},{11*0.305,3*0.305},{11*0.305,4*0.305},{11*0.305,5*0.305},{11*0.305,6*0.305},{11*0.305,7*0.305}};
double start[2] = {0.305, 9*0.305};
double goal[2] = {15*0.305, 5*0.305};
*/

/*
int num_obstacles = 15;

double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},
{1*0.305, 3*0.305}, {2*0.305, 3*0.305}, {3*0.305, 3*0.305}};

double start[2] = {10*0.305, 1*0.305};

double goal[2] = {3*0.305, 9*0.305};
*/

/*
int num_obstacles = 15;

double obstacle[MAX_OBSTACLES][2] =
{{4*0.305, 3*0.305},{5*0.305, 3*0.305},{6*0.305, 3*0.305},{7*0.305, 3*0.305},{8*0.305, 3*0.305},{9*0.305, 3*0.305},
{7*0.305, 6*0.305},{8*0.305, 6*0.305},{9*0.305, 6*0.305},{10*0.305, 6*0.305},{11*0.305, 6*0.305},{12*0.305, 6*0.305},
{1*0.305, 3*0.305}, {2*0.305, 3*0.305}, {3*0.305, 3*0.305}};

double goal[2] = {10*0.305, 1*0.305};

double start[2] = {3*0.305, 9*0.305};
*/

double walls[NUM_WALLS][2] =
{{0*0.305, 0*.305},{0*0.305, 1*.305},{0*0.305, 2*.305},{0*0.305, 3*.305},{0*0.305, 4*.305},{0*0.305, 5*.305},
{0*0.305, 6*.305},{0*0.305, 7*.305},{0*0.305, 8*.305},{0*0.305, 9*.305},{0*0.305, 10*.305},{16*0.305, 0*.305},
{16*0.305, 1*.305},{16*0.305, 2*.305},{16*0.305, 3*.305},{16*0.305, 4*.305},{16*0.305, 5*.305},
{16*0.305, 6*.305},{16*0.305, 7*.305},{16*0.305, 8*.305},{16*0.305, 9*.305},{16*0.305, 10*.305},
{1*0.305,0},{2*0.305, 0},{3*0.305, 0},{4*0.305, 0},{5*0.305, 0},{6*0.305, 0},{7*0.305, 0},{8*0.305, 0},
{9*0.305, 0},{10*0.305, 0},{11*0.305, 0},{12*0.305, 0},{13*0.305, 0},{14*0.305, 0},{15*0.305, 0},{16*0.305, 0},
{1*0.305,10*0.305},{2*0.305, 10*0.305},{3*0.305, 10*0.305},{4*0.305, 10*0.305},{5*0.305, 10*0.305},{6*0.305,10*0.305},
{7*0.305, 10*0.305},{8*0.305, 10*0.305},{9*0.305, 10*0.305},{10*0.305, 10*0.305},{11*0.305, 10*0.305},
{12*0.305, 10*0.305},{13*0.305, 10*0.305},{14*0.305, 10*0.305},{15*0.305, 10*0.305},{16*0.305, 10*0.305}};

typedef struct {
    int x;
    int y;
} Grid_Location;

int roundNo(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}

bool is_unseen(char c){
    return c == '_';
}

bool is_obstacle(int x, int y){
	int k;
    for(k = 0; k < num_obstacles; k++){
        if((roundNo(obstacle[k][0] / 0.305) == x) && (roundNo(obstacle[k][1] / 0.305) == y)){
            return true;
        }
    }
    return false;
}

void bfs(char room[17][11], int goal[2]){
    int current_round_size = 0, current_window_size = 0, previous_window_size = 0, blocks_from_goal = 1, i = 0;
    Grid_Location bfs_queue[1700];
    Grid_Location current_coordinates = {goal[0], goal[1]};
    bfs_queue[current_window_size++] = current_coordinates;
    while((current_window_size - previous_window_size) > 0){
        for(i = previous_window_size; i < current_window_size; i++){
            if(bfs_queue[i].x - 1 >= 0){
                if(is_unseen(room[bfs_queue[i].x - 1][bfs_queue[i].y])){
                    room[bfs_queue[i].x - 1][bfs_queue[i].y] = blocks_from_goal + '0';
                    Grid_Location current_coordinates = {bfs_queue[i].x - 1, bfs_queue[i].y};
                    bfs_queue[current_window_size + current_round_size++] = current_coordinates;
                }
            }
            if(bfs_queue[i].x + 1 < 17){
                if(is_unseen(room[bfs_queue[i].x + 1][bfs_queue[i].y])){
                    room[bfs_queue[i].x + 1][bfs_queue[i].y] = blocks_from_goal + '0';
                    Grid_Location current_coordinates = {bfs_queue[i].x + 1, bfs_queue[i].y};
                    bfs_queue[current_window_size + current_round_size++] = current_coordinates;
                }
            }
            if(bfs_queue[i].y - 1 >= 0){
                if(is_unseen(room[bfs_queue[i].x][bfs_queue[i].y - 1])){
                    room[bfs_queue[i].x][bfs_queue[i].y - 1] = blocks_from_goal + '0';
                    Grid_Location current_coordinates = {bfs_queue[i].x, bfs_queue[i].y - 1};
                    bfs_queue[current_window_size + current_round_size++] = current_coordinates;
                }
            }
            if(bfs_queue[i].y + 1 < 11){
                if(is_unseen(room[bfs_queue[i].x][bfs_queue[i].y + 1])){
                    room[bfs_queue[i].x][bfs_queue[i].y + 1] = blocks_from_goal + '0';
                    Grid_Location current_coordinates = {bfs_queue[i].x, bfs_queue[i].y + 1};
                    bfs_queue[current_window_size + current_round_size++] = current_coordinates;
                }
            }
        }
        blocks_from_goal++;
        previous_window_size = current_window_size;
        current_window_size += current_round_size;
        current_round_size = 0;
    }
}

void get_commands(int commands[50], char room[17][11], int goal[2], int start[2]){
    int current_position[2] = {start[0], start[1]};
    int i = 0, orientation = 1;
    while(goal[0] != current_position[0] || goal[1] != current_position[1]){
        int min = INT_MAX;
        int best_position[2];
        int current_command= 0;
        if(current_position[0] - 1 >= 0){
            if(room[current_position[0]-1][current_position[1]] != 'X'){
                if(room[current_position[0]-1][current_position[1]] < min){
                    min = room[current_position[0]-1][current_position[1]];
                    best_position[0] = current_position[0]-1;
                    best_position[1] = current_position[1];
                    current_command= -1;
                }
            }
        }
        if(current_position[0] + 1 < 17){
            if(room[current_position[0]+1][current_position[1]] != 'X'){
                if(room[current_position[0]+1][current_position[1]] < min){
                    min = room[current_position[0]+1][current_position[1]];
                    best_position[0] = current_position[0]+1;
                    best_position[1] = current_position[1];
                    current_command= 1;
                }
            }
        }
        if(current_position[1] - 1 >= 0){
            if(room[current_position[0]][current_position[1]-1] != 'X'){
                if(room[current_position[0]][current_position[1]-1] < min){
                    min = room[current_position[0]][current_position[1]-1];
                    best_position[0] = current_position[0];
                    best_position[1] = current_position[1]-1;
                    current_command= 2;
                }
            }
        }
        if(current_position[1] + 1 < 11){
            if(room[current_position[0]][current_position[1]+1] != 'X'){
                if(room[current_position[0]][current_position[1]+1] < min){
                    min = room[current_position[0]][current_position[1]+1];
                    best_position[0] = current_position[0];
                    best_position[1] = current_position[1]+1;
                    current_command= -2;
                }
            }
        }
        current_position[0] = best_position[0];
        current_position[1] = best_position[1];
        if(current_command!= orientation){
            if(current_command== 2 && orientation == 1){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 2;
            }else if(current_command== 1 && orientation == 2){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = 1;
            }else if(current_command== 1 && orientation == -2){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 1;
            }else if(current_command== -2 && orientation == 1){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = -2;
            }else if(current_command== -2 && orientation == -1){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -2;
            }else if(current_command== 2 && orientation == -1){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = 2;
            }else if(current_command== -1 && orientation == 2){
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -1;
            }else if(current_command== -1 && orientation == -2){
                commands[i++] = -2;
                commands[i++] = 1;
                orientation = -1;
            }else if(current_command== -1 && orientation == 1){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = -1;
            }else if(current_command== 1 && orientation == -1){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 1;
            }else if(current_command== 2 && orientation == -2){
                commands[i++] = 2;
                commands[i++] = 2;
                commands[i++] = 1;
                orientation = 2;
            }else if(current_command== -2 && orientation == 2){
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
	int i = 0, j = 0;
	for(i = 0; i < 50; i++){
		commands[i] = 0;
	}
	for(i = 0; i < NUM_WALLS; i++){
		int x = roundNo(walls[i][0] / 0.305);
		int y = roundNo(walls[i][1] / 0.305);
		room[x][y] = 'X';
	}
	for(i = 1; i < 16; i++){
		for(j = 1; j < 10; j++){
			if(roundNo(start[0] / 0.305) == i && roundNo(start[1] / 0.305) == j){
				room[i][j] = 'S';
			}else if(roundNo(goal[0] / 0.305) == i && roundNo(goal[1] / 0.305) == j){
				room[i][j] = 0;
			}
			else if(is_obstacle(i, j)){
				room[i][j] = 'X';
			}else{
				room[i][j] = '_';
			}
		}
	}
	int goal_ints[2] = {(int)roundNo(goal[0] / 0.305), (int)roundNo(goal[1] / 0.305)};
	int start_ints[2] = {(int)roundNo(start[0] / 0.305), (int)roundNo(start[1] / 0.305)};
	bfs(room, goal_ints);
	get_commands(commands, room, goal_ints, start_ints);
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
