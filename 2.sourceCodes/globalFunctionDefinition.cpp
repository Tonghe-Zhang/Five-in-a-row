#include "general.h"
#include <graphics.h>
#include "globalFunctionDeclaration.h"
#include "Neighbor.h"
#include "GUI_outputControl.h"
#include "Gui_inputControl.h"

void quickOutput(const char* sentence, int x, int y)
{

	settextcolor(RGB(30, 169, 225));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(sentence) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, sentence, _TRUNCATE);
	if (x == 0 && y == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 300, textOutput);
	else
		outtextxy(x, y, textOutput);
}


void quickOutput(const char* sentence, int x, int y, int R, int G, int B)
{
	settextcolor(RGB(R, G, B));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(sentence) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, sentence, _TRUNCATE);
	if (x == 0 && y == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 300, textOutput);
	else
		outtextxy(x, y, textOutput);
}

void quickOutput(string toBeOuput, int x, int y, int R, int G, int B)
{   char temp[150] = { " " };
	int i = 0;
	for (; i < 149 && i < toBeOuput.length(); i++)
		temp[i] = toBeOuput[i];
	temp[i] = '\0';
	quickOutput(temp, x, y, R, G, B);
}


void quickOutput(string toBeOuput, int x, int y)
{
	char temp[150] = { " " };
	int i = 0;
	for (; i < 149 && i < toBeOuput.length(); i++)
		temp[i] = toBeOuput[i];
	temp[i] = '\0';
	settextcolor(RGB(30, 169, 225));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(temp) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, temp, _TRUNCATE);
	if (x == 0 && y == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 300, textOutput);
	else
		outtextxy(x, y, textOutput);
}

//output at the lineNumber line in the middle.
void quickOutput(const char* sentence, const char* line, int lineNumber)
{
	settextcolor(RGB(30, 169, 225));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(sentence) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, sentence, _TRUNCATE);
	if (strcmp(line, "line") == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 300 + 40 * lineNumber, textOutput);
	else if (strcmp(line, "absoluteLine") == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 40 * lineNumber, textOutput);

}

void quickOutput(string toBeOuput, const char* line, int lineNumber)
{
	char temp[150] = { " " };
	int i = 0;
	for (; i < 149 && i < toBeOuput.length(); i++)
		temp[i] = toBeOuput[i];
	temp[i] = '\0';
	settextcolor(RGB(30, 169, 225));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(temp) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, temp, _TRUNCATE);
	if (strcmp(line, "line") == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 300 + 40 * lineNumber, textOutput);
	else if (strcmp(line, "absoluteLine") == 0)
		outtextxy(middleLineX - textLength / 2 * 10, 40 * lineNumber, textOutput);
}


void quickOutput(char* toBeOuput, int textPositionX, int textPositionY)
{
	settextcolor(RGB(30, 169, 225));
	settextstyle(40, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	size_t textLength = strlen(toBeOuput) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, toBeOuput, _TRUNCATE);
	outtextxy(textPositionX, textPositionY, textOutput);
}

//let the user input a safe and bidirectional decision(Y/N)
void YNInput(const char* notion, const char* answerA, const char* answerB)
{
	cin.clear();
	directive.clear();
	cleardevice();

	quickOutput(notion);
	int leftBoarder = middleLineX - (20) - strlen(answerA) * 10;
	int rightBoarder = middleLineX + (20) + strlen(answerB) * 20;
	quickOutput(answerA, leftBoarder, 350);
	quickOutput(answerB, rightBoarder, 350);

	ExMessage ms = getmessage(EM_MOUSE);
	while (true)
	{
		bool hasClikedRightPlace = false;
		if (hasClikedRightPlace)
			break;

		if (ms.message == WM_LBUTTONDOWN)
		{
			//fillcircle(ms.x, ms.y, 5);
			bool isOnBottonYes = (ms.x > leftBoarder && ms.x < middleLineX - 20 && ms.y < 400 && ms.y>300);
			bool isOnBottonNo = (ms.x > rightBoarder && ms.x < rightBoarder + strlen(answerB) * 10 && ms.y < 400 && ms.y>300);

			if (isOnBottonNo)
			{
				//fillcircle(ms.x, ms.y, 5);
				directive[0] = (answerB[0]);
				hasClikedRightPlace = true;
				break;
			}
			else if (isOnBottonYes)
			{
				directive[0] = (answerA[0]);
				hasClikedRightPlace = true;
				break;
			}
			else
			{
				ms = getmessage(EM_MOUSE);
			}
		}
		else
		{

			ms = getmessage(EM_MOUSE);

		}
	}

	if (strcmp(answerA, "Smart") == 0)
	{
		neighbor.range = (directive[0] == 'S' ? 10 : 3);
	}
}




void BasicInfoOutput(const char* notion, const char* answerA, const char* answerB)
{
	cin.clear();
	directive.clear();

	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(370, 300, 1500, 400);

	char buffer[100];
	strcpy(buffer, notion);
	Gui.outputTextWordByWord(buffer, 370, 300);
	int leftBoarder = middleLineX - (20) - strlen(answerA) * 10;
	int rightBoarder = middleLineX + (20) + strlen(answerB) * 20;
	if (strcmp(notion, "IN THIS GAME, YOU CAN.......") != 0)
	{
		quickOutput(answerA, leftBoarder, 350, 0, 255, 0);
		quickOutput(answerB, rightBoarder, 350, 0, 255, 0);
	}
	else
		return;
	ExMessage ms = getmessage(EM_MOUSE);
	while (true)
	{
		bool hasClikedRightPlace = false;
		if (hasClikedRightPlace)
			break;

		if (ms.message == WM_LBUTTONDOWN)
		{
			//fillcircle(ms.x, ms.y, 5);
			bool isOnBottonYes = (ms.x > leftBoarder && ms.x < middleLineX - 20 && ms.y < 400 && ms.y>300);
			bool isOnBottonNo = (ms.x > rightBoarder && ms.x < rightBoarder + strlen(answerB) * 10 && ms.y < 400 && ms.y>300);

			if (isOnBottonNo)
			{
				//fillcircle(ms.x, ms.y, 5);
				directive[0] = (answerB[0]);
				hasClikedRightPlace = true;
				break;
			}
			else if (isOnBottonYes)
			{
				directive[0] = (answerA[0]);
				hasClikedRightPlace = true;
				break;
			}
			else
			{
				ms = getmessage(EM_MOUSE);
			}
		}
		else
		{

			ms = getmessage(EM_MOUSE);

		}
	}

	if (strcmp(answerA, "Smart") == 0)
	{
		neighbor.range = (directive[0] == 'S' ? 10 : 3);
	}
}

void YNInput(const char* notion, const char* answerA,int numberOfAnswers)
{	
	cin.clear();
	directive.clear();
	cleardevice();
	quickOutput(notion);

	if (numberOfAnswers == 1)
	{
		int leftBoarder = middleLineX - strlen(answerA) / 2 * 10;
		int rightBorder = middleLineX + strlen(answerA) / 2 * 10;
		quickOutput(answerA, leftBoarder, 350);

		ExMessage ms = getmessage(EM_MOUSE);
		while (true)
		{
			bool hasClikedRightPlace = false;
			if (hasClikedRightPlace)
				break;
			if (ms.message == WM_LBUTTONDOWN)
			{
			
				bool isOnBottonYes = (ms.x > leftBoarder && ms.x < rightBorder&& ms.y < 400 && ms.y>300);
				if (isOnBottonYes)
				{
					directive[0] = (answerA[0]);
					hasClikedRightPlace = true;
					break;
				}
				else
				{
					ms = getmessage(EM_MOUSE);
				}
			}
			else
			{
				ms = getmessage(EM_MOUSE);
			}
		}
	}
}
//copy souce[start],...source[start+length-1] to destinaiton[0],destinaiton[length-1]
void getsubString(int* source, int start, int length, int* destination)
{

	for (int j = 0; j < length; j++)
	{
		destination[j] = *(source + start + j);
	}

}

//to test wether to integer arrays are identical.
bool equal(int* a, const int* b)
{
	for (int i = 0; i < 5; i++)
	{
		if (*(a + i) != *(b + i))
			return 0;
	}
	return 1;
}
