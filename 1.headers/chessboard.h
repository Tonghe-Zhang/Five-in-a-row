#pragma once
#pragma once
#include"general.h"

class chessboard
{
public:
	chessboard(int gs = 0, int pt = 1);
	//constructor.
	int board[16][16];
	//record the color of the stone in position(x,y)  empty, black, white;
	int sequence[16][16];
	//record which step it was when (i,j) was set.
	//row 0 and column 0 are signs that would tell the players their position.
	//row 1~15 and column 1~15 are the places to set stones.
	int weight[16][16][3];
	//weight: to evaluate the rank of danger of (i,j);
	//dimension 1&2: coordination.  dimension 3: [0]==weight. [1]==worst direction. [2]=distance between this point and its worst direction.


	void display();
	//to show current chessboard.
	bool test(int x, int y);
	//to verify whether this step(x,y) determines the winner.
	//if there is a five-nodes path from (x,y),return 1;else, return 0;

	void withdraw(int timeOfWithdrawal=1);
	//withdraw a misstep.Parameter: time of withdraw. When Parameter==1, it's a normal withdrawal operation. When Parameter==2, it's used by function "void retract()";
	void retract();
	//to retract what the player has just set.This function requires the array "board" be disgned as a 3-demensional cube.
	//the 3rd dimentsion will record the step in which this stone is set
	void reset();
	void instructions(bool mode);
	int game_status;
	//This is the index which indicates current state of this game.
	//0:start.   1~254:ongoing.    
	//255:full of stones,it's a tie.   
	//-1: someone quitted the game. 
	//-2: winner has been decided, end of game.
	//-99: displaying basic info.
	int player_s_turn;
	//let player_s_turn switch between 1 and 2.
	chessboard& operator ++();



};
extern chessboard gameboard;



