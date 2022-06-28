#pragma once
#include "general.h"
#include "chessboard.h"
#include "coordination.h"
//************************************************************************************************************************************************************
//class GUI


class GUI
{
private:
	char textStorage[15][200] =
	{
		" ",//use to escape unprepared initialization.
		"THIS IS A RETRACTABLE GOMOKU GAME DEVELOPED BY ALBERT COORPORATION.LTD.",
		"IN THIS GAME, YOU CAN.......",
		"CLICK THE CROSSINGS ON THE BOARD, TO SET A MOVE.",
		"CLICK BUTTON    [ WITHDRAW ],     TO WITHDRAW A MISSTEP." ,
		"CLICK BUTTON    [  RETRACT ],     TO RETRACT A MOVE." ,
		"CLICK BUTTON    [  RENAME ],      TO RESET USERNAME." ,
		"CLICK BUTTON [QUIT] OR PRESS [ESC],TO QUIT THIS GAME."
		" ",
		" ",
		" "
	};
	const char ad[50] = "#Ad: Albert Coorporation enpowers your business";
	void playMusic();

public:

	friend chessboard;
	friend void chessboard::instructions(bool mode);

	static enum fontPosition
	{
		middleX = 550,
		middleY = 300
	};

	static enum outputTextFormat
	{
		atMiddlePlace = 1
	};

	static enum instructionNumber
	{
		basicInfo = 0,
		options = 1,
		clearUpperLines = 2,
		clearMiddleLines=3,
		showPlayerTurn =4,
		computerOrHumanOrNet = 5,
		useRecordedGameboardOrNot = 6,
		playAgainOrNot = 7,
		saveTheGameboardOrNot = 8,
		endOfCalibration =9,
		showAdvertisement =10,
	};


	void initialization();
	void showIcon();
	GUI(int i) { ; }

	void outputText(char* toBeOuput, int textPositionX = middleX, int textPositionY = middleY, COLORREF rgb = RGB(30, 169, 225), int fontSize = 30, int intervalMiliSeconds = 50);
	void outputTextWordByWord(char* toBeOuput, int textPositionX = middleX, int textPositionY = middleY, COLORREF rgb = RGB(30, 169, 225), int fontSize = 30, int intervalMiliSeconds = 1200);
	void outputTextWordByWord(int textStorageSequence, int textPositionX = middleX-80, int textPositionY = middleY, COLORREF rgb = RGB(30, 169, 225), int fontSize = 30, int intervalMiliSeconds = 2500);
	void easyOutput(const char* sentence);
	void integratedOutputInstructions(int instructionSetNumber);
	
};
extern GUI Gui;


//************************************************************************************************************************************************************
//class gameboardPainter


class gameboardPainter :protected crd
{
public:
	static const int  gameboardScale;//Number of knobs on each line.
	static crd bottomeReferencePoints[20];
	static crd upperReferencePoints[20];
	static crd leftReferencePoints[20];
	static crd rightReferencePoints[20];
	static int deltaY;
	static int deltaX;
	inline void Mouse2Crd(int mx, int my, int* X, int* Y);
private:
	void referenceSetinitialization(int type, crd* pointSet, int  scale = gameboardScale);
	void initializeAllReferenceSets();

public:
	gameboardPainter(int i) { ; initializeAllReferenceSets(); }
	void drawGameboard(int  gameboardScale = gameboardScale);
	void Line(const crd& crd1, const crd& crd2);
	void setStone(int x, int y, int color);
	void setStone(int x, int y, int color, const char* inputType);
};




const enum boardRangeAndBoardType
{
	LeftDownBoarderX = 200,
	RightDownBoarderX = 1080,
	LeftUpBoarderX = 340,
	RightUpBoarderX = 940,
	middleLineX = 640,
	bottomBoarderY = 633,
	upperBoarderY = 60,
	middleLineY = 297,

	bottom = 1,
	upper = 2,
	left = 3,
	right = 4
};



const crd downLeft(LeftDownBoarderX, bottomBoarderY);
const crd upperLeft(LeftUpBoarderX, upperBoarderY);
const crd downRight(RightDownBoarderX, bottomBoarderY);
const crd upperRight(RightUpBoarderX, upperBoarderY);





