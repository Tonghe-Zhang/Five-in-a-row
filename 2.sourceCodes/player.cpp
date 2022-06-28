#include "general.h"
#include "player.h"
#include "chessboard.h"
#include "coordination.h"
#include "Neighbor.h"
#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"
#include "GUI_outputControl.h"
#include "GUI_button.h"


//For class player
void player::setname() { cin >> username; }
void player::setname(string name) { username = name; }

//Parameter: int x,int y are the relative coordinations of that stone.
//Return   : -1== winner has been decided/chessboard filled with stones.
//            0== this place is off chessboard/has been taken.
//            1== the place is safe to set a stone.
int player::verify(int x, int y)
{
	if (gameboard.game_status == -1)
	{

		quickOutput("<NOTION>This is the end of the game.");
		return -1;
	}
	if (gameboard.game_status == 225)
	{

		quickOutput("<NOTION>The chessboard is full of stone, this is a tie.");
		return -1;
	}
	if (!(x >= 1 && x <= 15 && y >= 1 && y <= 15))
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(350, 0, 1000, 40);
		quickOutput("<NOTION>This place is not on the board.Please select again.", 350, 0);
		Sleep(2000);
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(350, 0, 1000, 40);
		return 0;
	}
	if (gameboard.board[x][y])
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(350, 0, 1000, 40);
		quickOutput("<NOTION>This place has already been taken. Please select again.", 350, 0);
		Sleep(2000);
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(350, 0, 360 + strlen("<NOTION>This place has already been taken.Please select again.") * 10, 40);
		return 0;
	}
	return 1;
}

void player::setchess()
{
	//If the winner has been decided or this gameboard is filled with stones, exit this function.
	if (gameboard.game_status == -1 || gameboard.game_status == 225)
		return;

	bool hasClickedButton = false;
	bool withdrewOrRetracted = false;
	string textBuffer;
	int X = 0, Y = 0;                               //(X,Y) is the relative coordination on gameboard. (X,Y)（[1,15]〜[1,15]
	string temp1, temp2;
	gameboardPainter painter(15);

	//Show buttons at which this game just started.
	if (gameboard.game_status == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (isWithHuman == false && i == 2)
				continue;
			setfillcolor(BLACK);
			setlinecolor(BLACK);
			//fillrectangle(300, bottomBoarderY, 1500, bottomBoarderY+40);
			ptr[i]->startToUse(false);
		}
	}
	else if (gameboard.game_status==2&&isUsingNet==false)
	{
		for (int i = 0; i < 5; i++)
		{
			/*if (isWithHuman == false && i == 2)
				continue;*/
			
				ptr[i]->showButton();
				ptr[i]->startToUse(true);
		}
	}
	
	//If the player is human.
	if (!isRobot)
	{

		bool hasCliked = false;
		ExMessage mouse;
		while (true)
		{
			if (hasCliked)                                                  //1.Clicked on one of the buttons. 2. Clicked on the crossing on gameboard.
				break;
			mouse = getmessage(EM_MOUSE);                                   //Always detect a user's mouse movement.             
			if (mouse.message == WM_LBUTTONDOWN)                            //Only response when mouse is clicked.
			{                                       
				Button::clickPosition.x = mouse.x;
				Button::clickPosition.y = mouse.y;                        
				for (int buttonNumber =0; buttonNumber < 5; buttonNumber++) //If clicked, check whether the user clicked on the buttons.
				{
					if (ptr[buttonNumber]->hasClicked() == true)            //Valid click one : clicked on one of the buttons.
					{
						fun[buttonNumber](username);
						hasClickedButton = true;
						hasCliked = true;                                   
						if (buttonNumber == 1 || buttonNumber == 2)          //if clicked WithDraw or Retract
						{
							withdrewOrRetracted = true;
							
							
						}
					}
				}                                                          
				if (hasClickedButton == false)                              //Valid click two  :If it's not on the buttons, then it's on the chessboard.
				{
					painter.Mouse2Crd(mouse.x, mouse.y, &X, &Y);
					hasCliked = true;                                       //Exit when one valid click happened.
				}
			}
		}
	}
	//If the player is robot.
	else
	{
		crd XY = AIsetchess();
		X = XY.x;
		Y = XY.y;
	}

	//If the user withdrew or retracted, we won't veryfy it's move and will get back to main().
	if (gameboard.game_status == -1||withdrewOrRetracted)             		
		return;

    //Check whether the input is valid.
	int verifyResult = verify(X, Y);

	if (verifyResult == 1)                   //If this place is safe to set a stone.
	{
		gameboard.board[X][Y] = player_color;
		gameboard.sequence[X][Y] = (++gameboard.game_status);
		crd next(X, Y);
		neighbor.lastMoveStorage(player_color, next);

		//change gameboard.player_s_turn;
		gameboard.operator++();//++!!
		painter.setStone(X, Y, gameboard.board[X][Y]);

		//Check whethter this input results in end of game.
		if (gameboard.test(X, Y))
		{
			//Insert Music piece: Song of wanderer.

			Sleep(1000);
			textBuffer = "<NOTION> The WINNER is: ";
			textBuffer.append(username);
			quickOutput(textBuffer);
			Sleep(3500);
			gameboard.game_status = -2;
		}
		return;
	}
	else if (verifyResult == -1)           //If the winner has been decided/chess board filled with stones.
		return;







//************************************code change.
	else if (verifyResult == 0)            //If this is a wrong move.
	{ 
		if (isWithHuman == true)
			setchess();


	}
//************************************code change.
}












































crd player::AIsetchess()
{
	int enemyColor = ((*this).player_color) % 2 + 1;
	int n = neighbor.lastMoves[enemyColor][10].x;
	crd lastMove = neighbor.lastMoves[enemyColor][n - 1];
	crd nextMove = neighbor.nextMove(lastMove);

	if (nextMove == lastMove)
	{
		//an attack code should be placed here.
		//！！！！！！！！！！！！！！！！！！！！！！

		int k = 0;
		bool has_found = 0;


		if (lastMove.x == 0 && lastMove.y == 0)
		{
			nextMove.x = 7;
			nextMove.y = 7;
		}


		else
		{
			//find my last move.
			//get my last move.
			int color = (*this).player_color;
			int n = neighbor.lastMoves[color][10].x;
			crd mylastMove = neighbor.lastMoves[color][n - 1];
			//calculate my best move.
			nextMove = neighbor.nextMove(mylastMove);
			//if all directions are ok, then set chess beside the other player.
			if (nextMove == mylastMove)
			{
				while (!has_found)
				{
					k++;
					std::default_random_engine G;
					std::uniform_real_distribution<double> g(-100, 100);
					G.seed(time(NULL));
					int startPos = (g(G) > 0 ? 1 : -1);

					std::default_random_engine F;
					double range1 = 1, range2 = 399;

					if (lastMove.x < 5 && lastMove.y < 5)
					{
						range1 = 100;
						range2 = 299;
					}
					else if (lastMove.x > 10 && lastMove.y < 5)
					{
						range1 = 100;
					}
					else if (lastMove.x < 5 && lastMove.y >10)
					{
						range1 = 100;
						startPos = -1;
					}
					else if (lastMove.x > 10 && lastMove.y > 10)
					{
						range2 = 299;
						startPos = -1;
					}

					std::uniform_real_distribution<double> f(range1, range2);
					F.seed(time(NULL));
					int startDirection = (int)(f(F) / 100);

					/*cout << "k=" << k << " startDirection=" << startDirection << "  startPos==" << startPos << endl;
				*/


					for (int i = 0; i < 4; i++)
					{
						crd temp = startPos * k * v[(i + startDirection) % 4];

						crd test = lastMove + temp;

						bool safe = (test.x >= 1 && test.x <= 15 && test.y >= 1 && test.y <= 15);

						if (safe)
							if (gameboard.board[test.x][test.y] == chessColor::empty)
							{
								nextMove = test;
								has_found = true;
								break;
							}
					}

				}
			}

		}
	}
	Sleep(500);
	return nextMove;
}

