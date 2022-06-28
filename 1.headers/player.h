#pragma once
#include "COMMUNICATION.h"
#include "chessboard.h"
#include "coordination.h"
#include "GUI_button.h"

class player
{
public:
	player(int clr = 3, int vic = 0, string name = "untitiled", int retrac = 0, bool r = 0) :victory(vic), username(name), player_color(clr), retraction(retrac), isRobot(r) {};
	void setchess();
	void setname();
	void setname(string name);
	string username;
	bool isRobot;
	int retraction;
	int player_color;
	crd AIsetchess();
	static Button* ptr[6]; 
	static void (*fun[6])(string);
	friend Button;
	friend communicator;
private:
	int verify(int x, int y);
	//to check whether the input is valid or not.  Valid: 1  invalid: 0  end of game(no stones left): -1
	int victory;
	//to record how many times this winner has won.
};
extern player Player[3];

