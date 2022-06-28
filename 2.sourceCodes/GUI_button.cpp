#include "general.h"
#include "globalVariableDeclaration.h"
#include "GUI_button.h"

#define bugForRetract

crd Button::clickPosition = (0, 0);

Button buttonQuit("quit", RightDownBoarderX + 130, RightDownBoarderX + 220, upperBoarderY-65, upperBoarderY-25);
Button buttonRename("Rename", middleLineX - 200, middleLineX - 100, bottomBoarderY + 20,bottomBoarderY + 60);
Button buttonRetract("Retract", middleLineX - 100, middleLineX - 0, bottomBoarderY + 20,bottomBoarderY + 60);
Button buttonWithdraw("Withdraw", middleLineX + 0, middleLineX + 110, bottomBoarderY + 20,bottomBoarderY + 60);
Button buttonScore("Score", middleLineX + 110, middleLineX + 200, bottomBoarderY + 20,bottomBoarderY + 60);
Button buttonSkip("Skip", RightDownBoarderX + 130, RightDownBoarderX + 220, upperBoarderY - 65, upperBoarderY - 25);

void response(int i)
{
	fillcircle(200 + i * 50, 200, 10);
	Sleep(200);
	clearcircle(200 + i * 50, 200, 10);
	Sleep(200);
}

void Button::responseSkip(string username)
{
	;
}
void Button::responseRename(string username)
{
	;
}
void Button::responseRetract(string username)
{
	if (!gameboard.game_status)
	{
		cleardevice();
		return;
	}
	gameboard.retract();

	string line = username;
	line.append(" just made a retraction.");

	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(300, 0, 1000, 40);
	quickOutput(line, middleLineX - line.length() / 2 * 10, 0,255,0,255);
	Sleep(2000);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(300, 0, 1000, 40);

	return;
}
void Button::responseWithdraw(string username)
{
	gameboard.withdraw();
	string line = username;
	line.append(" just withdrew a misstep.");
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(300, 0, 1000, 40);
	quickOutput(line, middleLineX - line.length() / 2 * 10, 0, 255, 0, 255);
	Sleep(2000);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(300, 0, 1000, 40);
	return;
}
void Button::responseScore(string username)
{
	;
}
void Button::responseQuit(string username)
{
	cleardevice();
	quickOutput("You have just quitted the game.");
	Sleep(2000);
	gameboard.game_status = -1;
	return;
}
Button::Button(const char* textName, int left, int right, int up, int down)
{
	if (strlen(textName) > 9)
	{
		std::cerr << "text too long for this button.";
		exit(-1);
	}

	leftFringe = left; 	     rightFringe = right; 	     upperFringe = up;	         lowerFringe = down;

	upperLeft = (left, up);  lowerLeft = (left, down);   upperRight = (right, up);   lowerRight = (right, down);

	center.x = (left + right) / 2;
	center.y = (up + down) / 2;
	int i = 0;
	for (; i < 9; i++)
	{
		textOnBotton[i] = *(textName + i);
	}
	textOnBotton[i] = '\0';

	textLength = strlen(textOnBotton);

	hasStartToUse = false;
}
void Button::startToUse(bool useOrNot)
{
	hasStartToUse = useOrNot;
}
void Button::showButton()
{
	/*setlinecolor(RGB(255, 0, 225));

	rectangle(leftFringe, upperFringe, rightFringe, lowerFringe);
	setfillcolor(RGB(100, 200, 225));
	fillrectangle(leftFringe, upperFringe, rightFringe, lowerFringe);
	fillcircle(center.x, center.y, 3);
	cerr << "\nShowButton: x（(" << leftFringe + 10 << " , " << rightFringe - 10 << ")   y（(" << upperFringe << " , " << lowerFringe << ") " << endl;


*/

	if (strcmp(this->textOnBotton, "Skip") == 0)
	{
		quickOutput(textOnBotton, center.x - (textLength / 2) * 10, center.y - 23, 0, 255, 0);
		return;
	}
	quickOutput(textOnBotton, center.x - (textLength / 2) * 10, center.y - 23, 200, 0, 255);
}

void Button::hideButton()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(leftFringe, upperFringe, rightFringe, lowerFringe);
}
bool Button::hasClicked()
{
	/*setfillcolor(WHITE);
	fillcircle(Button::clickPosition.x, Button::clickPosition.y, 5);
	setfillcolor(BLACK);
	cerr << "hasStartToUse==" << hasStartToUse << endl;
	cerr << "clickPosition==" << "( " << clickPosition.x << " , " << clickPosition.y << ") " << endl;
	cerr << "x（(" << leftFringe + 10 << " , " << rightFringe - 10 << ")   y（(" << upperFringe << " , " << lowerFringe <<") "<< endl;
	cerr<<" is in range? "<< (hasStartToUse && clickPosition.x > leftFringe + 10 && clickPosition.x < rightFringe - 10 && clickPosition.y<lowerFringe&& clickPosition.y > upperFringe);*/

	return(hasStartToUse && clickPosition.x > leftFringe + 10 && clickPosition.x<rightFringe - 10 && clickPosition.y<lowerFringe && clickPosition.y > upperFringe);
}