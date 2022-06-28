#pragma once
#include "general.h"
#include "GUI_outputControl.h"
#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"
#include "globalVariableDeclaration.h"

//This is the base class of all sorts of buttons.
class Button
{
private:
	int  leftFringe, rightFringe, upperFringe, lowerFringe;                              //The coordinations of four fringes.
	crd  upperLeft, upperRight, lowerLeft, lowerRight, center;
	//void drawLine(const crd& p1, const crd& p2);
	char textOnBotton[10];
	int  textLength;
	bool hasStartToUse;                                                                  //whether this button is being used.
	//void (*response)();                                                                //A pointer that points to the function for giving reponse after clicking this button.
	ExMessage m;
public:
	Button(const char* textName, int left = 0, int right = 0, int up = 0, int down = 0); //Constructor. Parameters: textName and the cordinations of its four fringes.
	void startToUse(bool useOrNot);                                                      //Whether this button is being used.
	void showButton();                                                          
	void hideButton();
	bool hasClicked();                                                                   //Whether the user has clicked on this button.
	static crd clickPosition;
	static void responseRename(string);
	static void responseRetract(string);
	static void responseWithdraw(string);
	static void responseScore(string);
	static void responseQuit(string);
	static void responseSkip(string);
	friend STAR;
};