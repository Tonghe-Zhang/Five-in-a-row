#include "GUI_outputControl.h"
#include "GUI_inputControl.h"
#include "globalVariableDeclaration.h"
#include "globalFunctionDeclaration.h"
#include "player.h"
#include "globalVariableDeclaration.h"
#include "fileManagement.h"

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#pragma comment(lib, "Winmm.lib")    // 引用 Windows Multimedia API
#include "resource.h"     // 注：如果资源 ID 为宏定义，请取消这行注释
#pragma warning (disable:4996)
#define CRT_SECURE_NO_WARNINGS

#include "GUI_outputControl.h"






//#define DEBUG
// 
//************************************************************************************************************************************************************
//class GUI
void GUI::initialization()
{
	
	showIcon();
	setbkcolor(BLACK);
	cleardevice();
	setbkmode(TRANSPARENT); // text output background be transparant.
	Gui.playMusic();//Starts to play music.

}
void GUI::showIcon()
{
	initgraph(pictureWidthX, pictureWidthY); // create a graph with designated width and height.
	//Show Icon.
	setbkcolor(BLACK);
	IMAGE imag;
	loadimage(&imag, L"JPG", MAKEINTRESOURCE(AlbertCorpIcon));
	putimage(middleLineX - 120, middleLineY, &imag);
	quickOutput("Albert coorporation empowers your business.", "line", 4);
	Sleep(2500);
	cleardevice();
}

void GUI::outputText(char* toBeOuput, int textPositionX, int textPositionY, COLORREF rgb, int fontSize, int intervalMiliSeconds)
{
	settextcolor(rgb);
	settextstyle(fontSize, 10, L"Times New Roman", 0, 0, 100, true, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);

	size_t textLength = strlen(toBeOuput) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, toBeOuput, _TRUNCATE);
	outtextxy(textPositionX, textPositionY, textOutput);
	Sleep((DWORD)intervalMiliSeconds);
}


void GUI::outputTextWordByWord(char* toBeOuput, int textPositionX, int textPositionY, COLORREF rgb, int fontSize, int intervalMiliSeconds)
{
	settextcolor(rgb);
	settextstyle(fontSize, 10, L"Times New Roman", 0, 0, 100, false, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);

	size_t textLength = strlen(toBeOuput) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, toBeOuput, _TRUNCATE);
	if (textOutput != NULL)
	{
		int lengthOfLastCharacters = 0;

		for (int i = 0; i < textLength; i++)
		{

			outtextxy(textPositionX + lengthOfLastCharacters, textPositionY, *(textOutput));
			Sleep(35);
			lengthOfLastCharacters += textwidth(*textOutput);
			textOutput++;

		}
	}
	Sleep((DWORD)intervalMiliSeconds);
}





void GUI::easyOutput(const char* sentence)
{
	char temp[200];
	strcpy(temp, sentence);
	outputText(temp);
}



void GUI::outputTextWordByWord(int textStorageSequence, int textPositionX, int textPositionY, COLORREF rgb, int fontSize, int intervalMiliSeconds)
{
	//int startPositionX = textPositionX - strlen(textStorage[textStorageSequence] )/ 2 * 10;

	settextcolor(rgb);
	settextstyle(fontSize, 10, L"Times New Roman", 0, 0, 100, false, false, false, 0, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	
	size_t textLength = strlen(textStorage[textStorageSequence]) + 1;
	size_t converted = 0;
	wchar_t* textOutput;
	textOutput = (wchar_t*)malloc(textLength * sizeof(wchar_t));
	mbstowcs_s(&converted, textOutput, textLength, textStorage[textStorageSequence], _TRUNCATE);


	if (textOutput != NULL)
	{
		int lengthOfLastCharacters = 0;

		for (int i = 0; i < textLength; i++)
		{

			outtextxy(textPositionX + lengthOfLastCharacters, textPositionX, *(textOutput));
			Sleep(35);
			lengthOfLastCharacters += textwidth(*textOutput);
			textOutput++;

		}
	}
	Sleep((DWORD)intervalMiliSeconds);
}


// You shold place the music in the same folder where the exe. file is placed when releasing this project.
//                 for example, for development use, background music should be put at:   C:\Users\tongh\source\repos\ConsoleApplication1\ConsoleApplication1 
// 
//
void GUI::playMusic()
{
	//Open temporary file name.
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat(tmpmp3, _T("testapp_background.mp3"));                  //VC2008、VC2010 should use _tcscat_s or add #define CRT_SECURE_NO_WARNINS 

	//Extract mp3 file as a temporary file.
	//ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
	//if the ID of mp3 resource is defined as IDR_MP31,then write MAKEINTERSOURCE(IDR_MP31);
	ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(Pavane/*IDR_MP31*/));

	//Open music file.
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);    //VC2008、VC2010 should use _tcscat_s or add #define CRT_SECURE_NO_WARNINS 
	mciSendString(mcicmd, NULL, 0, NULL);

	//Play music.
	mciSendString(_T("play mymusic"), NULL, 0, NULL);

	//if (gameboard.game_status == -1)
	//{
	//	mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	//	mciSendString(_T("close mymusic"), NULL, 0, NULL);

	//	// Delete temporary file.
	//	DeleteFile(tmpmp3);
	//}
}

//This is an 
//  interface to ouput different sets of instructions.
//Good thing is that , using enum type, the programmer can write readable codes and leave all those operations to  this integrated surface.
void GUI::integratedOutputInstructions(int instructionSetNumber)
{
	string temp = "Now goes  ";
	gameboardPainter Painter(15);

	switch (instructionSetNumber)
	{
	case GUI::instructionNumber::basicInfo:
	{
		Gui.outputTextWordByWord(0, 0, 0);
		char sentenceONe[100] = { "THIS IS A GOMOKU GAME DEVELOPED BY ALBERT COORPORATION.LTD." };
		outputTextWordByWord(sentenceONe, middleLineX - strlen(sentenceONe)/ 2 * 15,300);
		Gui.integratedOutputInstructions(GUI::instructionNumber::clearMiddleLines);

		for (int i = 2; i < 8; i++)
		{
			directive.clear();
			BasicInfoOutput(textStorage[i], "Next", "Skip");
			if (directive[0] == 'S')
			{
				cleardevice();
				return;
			}
		}
		break;
	}

	
	case GUI::instructionNumber::options:
	{
		outputTextWordByWord(11, 300, 300);
		outputTextWordByWord(12, 300, 300);
		outputTextWordByWord(13, 300, 300);
		break;
	}

	case GUI::instructionNumber::clearUpperLines:
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		fillrectangle(300, 0, 1000, 40);
		break;
	}

	case GUI::instructionNumber::clearMiddleLines:
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(0, 300, pictureWidthX, 400);
		break;
	}

	case GUI::instructionNumber::showPlayerTurn:
	{
		setfillcolor(BLACK); setlinecolor(BLACK); fillrectangle(300, 0, 1000, 40);
		//string temp=="Now goes";

		temp.append(Player[gameboard.player_s_turn].username);
		quickOutput(temp, "absoluteLine", 0);
		break;
	}

	case  GUI::instructionNumber::computerOrHumanOrNet:
	{
		Sleep(500);
		YNInput("Would you like to combat with the COMPUTER or combat with your FRIEND?", "Computer", "Friend");
		if (directive[0] == 'C')
		{
			cleardevice();
			::isWithHuman = false;
			YNInput("Would you like the computer to be SMART or FOOLISH?", "Smart", "Foolish");
		}
		else if (directive[0] == 'F')
		{
			cleardevice();
			directive.clear();
			YNInput("Are your friend using the same device or not?","Same","Different");
			if (directive[0]=='D')
			{
				::isUsingNet = true;
				cleardevice();
				quickOutput("Then you will use the Internet to share gameboard.Press any key to continue");
				system("pause");
			}
		}
		cleardevice();
		break;
	}

	case GUI::instructionNumber::playAgainOrNot:
	{

		cleardevice();
		YNInput("Would you like to PLAY AGAIN?");
		if (directive[0] == 'N')
		{
			playAgain = false;
			cleardevice();
			if (gameboard.game_status != -2)//Only record those boards that haven't decided the winner.Otherwise, when the gameboard is reloarded, you can't play.
			{
				cleardevice();
				Gui.integratedOutputInstructions(GUI::instructionNumber::saveTheGameboardOrNot);
			}
		}
		break;
	}
	case GUI::instructionNumber::saveTheGameboardOrNot:
	{
		
		YNInput("Would you like to SAVE the gameboard?");
		if (directive[0] == 'Y')
		{
			//未改完
			fileKeeper.createFolder_and_Files();
			fileKeeper.recordGameboard();
			fileKeeper.closeFiles();
		}
		break;
	}

	case GUI::instructionNumber::useRecordedGameboardOrNot:
	{
		if (::isUsingNet)
			return;
		YNInput("Would you like to use HISTORY GAMEBOARDS?");
		if (directive[0] == 'Y' || directive[0] == 'y')
		{
			cleardevice();

			if (fileKeeper.checkAndChooseFilename())
			{
				fileKeeper.readInGameboardData();
			}
			cleardevice();

		}
		break;
	}

	case GUI::instructionNumber::endOfCalibration:
	{
		if (::isUsingNet)
			return;
		cleardevice();
		::GUI_mode = playing;                                                      //Stars to play.
		Painter.drawGameboard();                                                   //Draw gameboard. Lines first, stones later.
		break;
	}

	case GUI::instructionNumber::showAdvertisement:
	{
		cleardevice();
		quickOutput(ad);
		Sleep(3500);
		cleardevice();
		quickOutput("Perfect Gomaku was first created by Albert Zhang on March 8th, 2022.");
		Sleep(4200);
		cleardevice();
		quickOutput("Thanks for playing", middleLineX - strlen("Thanks for playing") / 2 * 10, 300);
		Sleep(2000);
		::GUI_mode = endOfGame;
		Sleep(7000);
		break;
	}
	}
}

//************************************************************************************************************************************************************
//class gameboardPainter

void gameboardPainter::Line(const crd& crd1, const crd& crd2)
{
	line(crd1.x, crd1.y, crd2.x, crd2.y);
}


void gameboardPainter::setStone(int x, int y, int color)
{
	switch (color)
	{
	case  chessColor::black:
		setlinecolor(RGB(0, 0, 255));
		setfillcolor(RGB(0,0,0));
		break;
	case  chessColor::white:
		setlinecolor(RGB(255, 255, 255));
		setfillcolor(RGB(240, 240, 240));
		break;
	case chessColor::empty:
		return;
	}
	fillcircle
	((int)((x - 1) * (gameboardPainter::bottomeReferencePoints[y - 1].x - gameboardPainter::upperReferencePoints[y - 1].x) / (gameboardPainter::gameboardScale - 1) + gameboardPainter::upperReferencePoints[y - 1].x),
		gameboardPainter::leftReferencePoints[gameboardPainter::gameboardScale - x].y,
		10);
}

void gameboardPainter::referenceSetinitialization(int type, crd* pointSet, int  S)
{
	int scale = S;
	switch (type)
	{
	case boardRangeAndBoardType::bottom:
		for (int i = 0; i < scale; i++)
		{
			pointSet[i].changeCoordination(LeftDownBoarderX + i * (RightDownBoarderX - LeftDownBoarderX) / (scale - 1), bottomBoarderY);
		}
		break;
	case boardRangeAndBoardType::upper:
		for (int i = 0; i < scale; i++)
		{
			pointSet[i].changeCoordination(LeftUpBoarderX + i * (RightUpBoarderX - LeftUpBoarderX) / (scale - 1), upperBoarderY);
		}
		break;
	case boardRangeAndBoardType::left:
		for (int i = 0; i < scale; i++)
		{
			pointSet[i].changeCoordination(LeftDownBoarderX + i * (LeftUpBoarderX - LeftDownBoarderX) / (scale - 1), bottomBoarderY + i * (upperBoarderY - bottomBoarderY) / (scale - 1));
		}
		break;
	case boardRangeAndBoardType::right:
		for (int i = 0; i < scale; i++)
		{
			pointSet[i].changeCoordination(RightDownBoarderX + i * (RightUpBoarderX - RightDownBoarderX) / (scale - 1), bottomBoarderY + i * (upperBoarderY - bottomBoarderY) / (scale - 1));
		}
		break;
	}

}

void gameboardPainter::initializeAllReferenceSets()
{
	referenceSetinitialization(boardRangeAndBoardType::bottom, bottomeReferencePoints);
	referenceSetinitialization(boardRangeAndBoardType::upper, upperReferencePoints);
	referenceSetinitialization(boardRangeAndBoardType::left, leftReferencePoints);
	referenceSetinitialization(boardRangeAndBoardType::right, rightReferencePoints);

}

void gameboardPainter::drawGameboard(int  gameboardScale)
{
	setlinecolor(RGB(100, 200, 255));
	setlinestyle(PS_SOLID, 0.01);
	Line(downRight, upperRight);
	Line(upperRight, upperLeft);
	Line(upperLeft, downLeft);
	Line(downLeft, downRight);

	for (int i = 0; i < gameboardScale; i++)
	{
		Sleep(i < 5 ? 200 : 0);
		Line(upperReferencePoints[gameboardScale - i - 2], bottomeReferencePoints[gameboardScale - i - 2]);

		Line(leftReferencePoints[gameboardScale - i - 1], rightReferencePoints[gameboardScale - i - 1]);

		Line(upperReferencePoints[i], bottomeReferencePoints[i]);

		Line(leftReferencePoints[i], rightReferencePoints[i]);

	}
	Sleep(500);
	gameboard.display();
}


inline void gameboardPainter::Mouse2Crd(int mx, int my, int* X, int* Y)
{
	double deltaY = gameboardPainter::leftReferencePoints[1].y - gameboardPainter::leftReferencePoints[0].y;

	*X = floor(0.5 + (((double)(my - gameboardPainter::leftReferencePoints[0].y)) / (deltaY)));
	*X = gameboardPainter::gameboardScale - *X;

	int x0 = gameboardPainter::leftReferencePoints[gameboardPainter::gameboardScale - *X].x;
	double deltaX = ((double)(gameboardPainter::rightReferencePoints[gameboardPainter::gameboardScale - *X].x - gameboardPainter::leftReferencePoints[gameboardPainter::gameboardScale - *X].x)) / (gameboardPainter::gameboardScale - 1);

	*Y = 1 + floor(0.5 + (((double)(mx - x0)) / (deltaX)));
}

void gameboardPainter::setStone(int mx, int my, int color, const char* inputType)
{
	if (strcmp(inputType, "mouse") == 0)
	{
		int X = 0, Y = 0;
		Mouse2Crd(mx, my, &X, &Y);
		setStone(X, Y, color);
	}
}