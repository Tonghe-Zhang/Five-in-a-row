#pragma once
#include<iostream>
using namespace std;

extern bool playAgain;
//Global constants & vavirables' declarations.
extern bool isWithHuman;
//mode 0==compete with computer. mode 1==compete with human.
extern bool isUsingNet;
//0==not using net. 1==using IPV4






extern int play_times;
//a global integer to record times of play in this game.this will be used to generate different files which record different gamboards of different rounds.
//play_times ranges from 0 to 99;
extern int X;
extern int Y;
extern int pictureWidthY;
extern int pictureWidthX;
extern int GUI_mode;
const enum chessColor
{
	empty = 0,
	black = 1,
	white = 2
};
const enum GuiModeType
{
	start = 1,
	basicInfo = 2,
	playing = 3,
	endOfGame = 4,
};


extern string name1;
extern string name2;
//dircetion typed in by the two players.
extern string directive;
//playerOne and playerTwo's names.
extern string filename;


//predeclaration of the Classes. 
class chessboard;
class crd;
class player;
class Neighbor;
class fileManager;
class GUI;
class STAR;
class Button;
class communicator;

//predeclaration of Global objects.
extern crd buffer;
//to store temporary results from coordination calculations.(to save data returned from a funciton.) 
extern Neighbor neighbor;

extern Button buttonRename, buttonRetract, buttonWithdraw, buttonScore, buttonQuit, buttonSkip;

extern GUI Gui;
