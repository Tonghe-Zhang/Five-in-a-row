#include "thread"
#include "general.h"
#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"
#include "chessboard.h"
#include "fileManagement.h"
#include "Neighbor.h"
#include "player.h"
#include "GUI_backgroundStarryNight.h"
#include "Gui_inputControl.h"
#include "GUI_outputControl.h"
#include "GUI_button.h"

#define DEBUG false

DWORD WINAPI threadBackground(LPVOID lpParameter)
{
	STAR::showStarryNight();
	return 0L;
}


void mainForNet();

int main()
{
	while (::playAgain)
	{
		Gui.initialization();                                                                                   //Initialize data.
		play_times++;
		gameboard.reset();
		directive.clear();
		ExMessage m;
		gameboardPainter Painter(15);

		HANDLE thread = CreateThread(NULL, 0, threadBackground, NULL, 0, NULL);
		if (thread)
		{
			CloseHandle(thread);
		}

		Gui.integratedOutputInstructions(GUI::basicInfo);                                                       //Give basic instructions.
		Gui.integratedOutputInstructions(GUI::computerOrHumanOrNet);                                            //Select game modes: to play with Computer or Human player.If with human player, use the internet or not.
		Gui.integratedOutputInstructions(GUI::useRecordedGameboardOrNot);                                       //Select game modes: useRecordedGameboardOrNot.
		gameboard.instructions(isWithHuman);                                                                    //Enter username and decide who goes first.
		Gui.integratedOutputInstructions(GUI::endOfCalibration);                                                //End of calibration.
		if (::isUsingNet)
			mainForNet();
		else
		{
			while (gameboard.game_status != 225 && gameboard.game_status != -1 && gameboard.game_status != -2) 	//Start to detect user's keyboard and mouse.
			{
					Gui.integratedOutputInstructions(GUI::showPlayerTurn);
					Player[gameboard.player_s_turn].setchess();
			}
		}
		Gui.integratedOutputInstructions(GUI::playAgainOrNot);  //If user quits...
	}
	Gui.integratedOutputInstructions(GUI::showAdvertisement);
	
	::GUI_mode = playing;
	Gui.showIcon();
	::GUI_mode = start;
	return 0;
}

void mainForNet()
{

	isUsingNet = true;
	communicator SERVER(true);
	communicator CLIENT(false);
	directive.clear();
	cleardevice();

	::GUI_mode = playing;

	string userName;
	quickOutput("Please type in your user name");
	InputText(&userName);

	YNInput("Who wants to move first?", "Me", "Friend");
	//Client starts first.
	if (directive[0] == 'F')
	{
		//Then you will be the server,Starts firs, moves later.
		Player[2].setname(userName);

		cleardevice();
		SERVER.getServerIP(true);
		SERVER.communicate();
	}
	else
	{
		//Then you will be the client,starts later, moves first.
		Player[1].setname(userName);
		cleardevice();
		quickOutput("Please type in your FRIEND'S IP adress.");
		Sleep(2000);
		CLIENT.getServerIP(false);
		CLIENT.communicate();
	}
	cleardevice();

}