#include "general.h"
#include "chessboard.h"
#include "coordination.h"
#include "player.h"
#include "Neighbor.h"
#include "globalVariableDeclaration.h"
#include <graphics.h>

#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"

#include "Gui_inputControl.h"
#include "GUI_outputControl.h"
#include "GUI_backgroundStarryNight.h"

using namespace std;

//#define DEBUG

//#define bugForRetract

chessboard::chessboard(int gs, int pt)
{
	game_status = gs;
	player_s_turn = pt;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{

			this->sequence[i][j] = 0;
			this->board[i][j] = chessColor::empty;
			for (int k = 0; k < 3; k++)
				this->weight[i][j][k] = 0;
		}
}

void chessboard::instructions(bool isWithHuman)
{
	if (::isUsingNet)
	{
		return;
	}

	string tempName;

	if (isWithHuman == true)
	{
#ifndef DEBUG
		cleardevice();
		quickOutput("Please designate players' usernames.");
		quickOutput("Player one ", "line", 1);
		InputText(&name1);

		quickOutput("Player two ", "line", 1);
		InputText(&name2);

		cleardevice();
		quickOutput("We will pick a player to move first randomly", "line", 0);
		Sleep(2500);
#endif // DEBUG


	}
	else
	{
		cleardevice();
		quickOutput("Please type in your username.");
		quickOutput("Username", "line", 1);
		InputText(&name1);
		cleardevice();
		Sleep(500);
		name2 = name1;
		name2.append("'s Nightmare(AI)\0");
		tempName.append("Computer's username:").append(name2);
		Sleep(1500);
#ifndef DEBUG 
		cleardevice();
		quickOutput(tempName);
		Sleep(2500);
		cleardevice();
		quickOutput("We will pick a player to move first randomly", "line", 0);
		Sleep(1500);
#endif // !DEBUG 
	}

	const string computerName = name2;

	//randomly switch player's turns, by swapping their names.
	std::srand((unsigned)time(NULL));
	int term = rand() % 2;
	if (!term)
	{
		tempName = name1;
		name1 = name2;
		name2 = tempName;
	}


	Player[1].setname(name1);
	Player[2].setname(name2);

	if (isWithHuman == false)
	{
		if (Player[1].username == computerName)
			Player[1].isRobot = true;
		else if (Player[2].username == computerName)
			Player[2].isRobot = true;
	}

	cleardevice();

#ifndef DEBUG
	Sleep(500);
	tempName = name1;
	tempName.append(" will take black stones.");
	quickOutput(tempName);
	tempName = name2;
	tempName.append(" will take white stones.");
	quickOutput(tempName,"line",1);
	tempName = name1;
	tempName.append("moves first.");
	quickOutput(tempName,"line", 2);
	Sleep(3000);
	cleardevice();
	cleardevice();
	quickOutput("<NOTION> This game will start in 3 seconds.");
	Sleep(1000);
	quickOutput("<NOTION> This game will start in 2 seconds.");
	Sleep(700);
	quickOutput("<NOTION> This game will start in 1 second .");
	Sleep(600);
	cleardevice();
	gameboard.game_status = 0;
#endif // DEBUG
}

void chessboard::display()
{
	gameboardPainter painter(15);
	for (int i = 1; i < 16; i++)
		for (int j = 1; j < 16; j++)
		{
			painter.setStone(i, j, gameboard.board[i][j]);
		}
}



bool chessboard::test(int x, int y) //test(x,y)==1 : winner is decided.  test(x,y)==0: winner hasn't been decided.
{

	crd here(x, y);
	//neighbor.testNeighbor(here);



	const crd p(x, y);
	int color = gameboard.board[x][y];
	//store the information carried by (x,y).
	crd q = p;
	//q is a temperary variable used to record the colors of surrounding stones.
	int same_color = 1, flag = 1;
	//flag denotes the numbers of stones found in this round whose color is identical to that of (x,y);
	//same_color denotes max{flag};
	//v[i] unit vectors
	int i = 0;
	for (; i < 4; i++)//4*2=8 directions
	{
		flag = 1;
		while ((q + v[i]).color() == color)
		{
			flag++;
			q = q + v[i];
			//cout << "\nSame color found in position: +v[" << i << "]";
		}
		q = p;

		while ((q - v[i]).color() == color)
		{
			flag++;
			q = q - v[i];
			//cout << "\nSame color found in position: -v[" << i << "]";
		}

		//cout << "\n!!There are flag=="<<flag<<" same color stones on position : ¡Àv[" << i << "] !!";

		if (flag > same_color)
		{
			same_color = flag;
			//cout << "\n@@Maximum of same color stones rise to same_color==" << same_color << " .";
		}
		if (same_color == 5)
		{
			//quickOutput( "<NOTION>!!!!That's the End Of the Game!\n";
			return 1;
		}
	}

	//cout << "\nIn the End: the direction with the most same color stones: I==" << i << "\tNumber of Same color stones: same_color==" << same_color << "\n";

	return 0;
}

void chessboard::withdraw(int timeOfWithdraw)
{	//Find the previous move,then make it empty.      

	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(LeftDownBoarderX-10, upperBoarderY-10, RightDownBoarderX+10, bottomBoarderY);

	int i = 0, j = 0;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++)
			if (gameboard.sequence[i][j] == gameboard.game_status)//find last move.
			{
				int color = gameboard.board[i][j];
				int n = neighbor.lastMoves[color][10].x;
				//find that player who set the last move and make it "empty".
				if (n)
				{
					neighbor.lastMoves[color][n - 1].x = 0;
					neighbor.lastMoves[color][n - 1].y = 0;
				}
				//decrease number of stones set by that player.
				neighbor.lastMoves[color][10].x--;
				gameboard.board[i][j] = chessColor::empty;

				break;
			}
	while (gameboard.game_status > 1)
	{
		setfillcolor(BLACK);
		setlinecolor(BLACK);
		fillrectangle(300, 0, 1000, bottomBoarderY);
		
		if (timeOfWithdraw == 1)
		{
			gameboardPainter painter(15);
			painter.drawGameboard();
			gameboard.display();
		}

		gameboard.operator++();//Change gameboard.player_s_turn.
		gameboard.game_status--;

		return;
	}
	cleardevice();
	quickOutput("<NOTION>You have just went back to the start of this game.");
	Sleep(2000);
	cleardevice();
	quickOutput("<NOTION> This game will start in 3 seconds.");
	Sleep(800);
	quickOutput("<NOTION> This game will start in 2 seconds.");
	Sleep(700);
	quickOutput("<NOTION> This game will start in 1 second.");
	Sleep(500);
	cleardevice();
	gameboard.game_status = 0;
}

void chessboard::retract()
{	
	withdraw(2);
	withdraw(2);
	gameboardPainter painter(15);
	painter.drawGameboard();
	gameboard.display();
}

void chessboard::reset()
{
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			gameboard.board[i][j] = 0;
			gameboard.sequence[i][j] = 0;
		}
	gameboard.game_status = 0;
}

//swap player 1 and player 2 's turns, allow player_s_turn to change within {1,2}
chessboard& chessboard::operator ++()
{
	this->player_s_turn = 2 - (this->player_s_turn + 1) % 2;
	return (*this);
}