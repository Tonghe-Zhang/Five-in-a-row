#include "GUI_backgroundStarryNight.h"
#include "GUI_outputControl.h"
#include "globalVariableDeclaration.h"
#include "GUI_button.h"



STAR::STAR(int i)
{
	InitStar(i, start);
}

inline void STAR::InitStar(int i, int mode)
{
	star[i].x = 0;
	star[i].y = rand() % pictureWidthY;
	switch (mode)
	{
	case endOfGame:
		while (star[i].y < 340 && star[i].y>300)
			star[i].y = rand() % pictureWidthY;
		break;
	case start:
		while (star[i].y < 432 && star[i].y>300)
			star[i].y = rand() % pictureWidthY;
		break;

	case playing:
		bool inBoarderY = star[i].y > upperBoarderY - 65 && star[i].y < upperBoarderY - 25;//(star[i].y > upperBoarderY-20&& star[i].y>bottomBoarderY);
		while (inBoarderY)
		{
			star[i].y = rand() % pictureWidthY;
			inBoarderY = star[i].y > upperBoarderY - 65 && star[i].y < upperBoarderY - 25;//(star[i].y < upperBoarderY-20&& star[i].y>bottomBoarderY);
		}
		break;
		//Old version:


	}



	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	//the faster, the brighter.
	star[i].color = RGB(255, 255, 255);//star[i].color, star[i].color, star[i].color);
}


inline void STAR::MoveStar(int i, int mode)
{
	// rub off previous stars. This is actually painting a black dot on previous position.

	if (mode != GuiModeType::endOfGame)
	{
		putpixel((int)star[i].x, star[i].y, 0);
	}
	// recalculate position.

	star[i].x += star[i].step / 5;
	if (mode == GuiModeType::playing)
	{
		if (star[i].x > LeftDownBoarderX && star[i].x < RightDownBoarderX)
		{
			star[i].x = RightDownBoarderX;
		}
	}
	if (star[i].x > pictureWidthX)//||inboarderY)	
		InitStar(i, mode);

	//draw a new star.
	putpixel((int)star[i].x, star[i].y, star[i].color);
	//fillcircle((int)star[i].x, star[i].y,1);
}



void STAR::showStarryNight()
{
	ExMessage m;
	srand(NULL);
	initgraph(pictureWidthX, pictureWidthY);
	for (int i = 0; i < MAXSTAR; i++)
	{
		star[i].InitStar(i, ::GUI_mode);
	}

	if (::GUI_mode == playing)
	{
		cleardevice();
		system("pause");
		system("pause");
	}
	//Now this thread will keep on running until this programme is shut down.
	                   //currently, starry night will stop running until the user press ESC.
	while (true)               //Another way to stop this thread is to check any hit on the keyboard. /*!_kbhit()*///kbhit is a boolean varianble indicating a hit of any key.
	{
		for (int i = 0; i < MAXSTAR; i++)
			star[i].MoveStar(i, ::GUI_mode);
	}
	gameboard.game_status = -1;

	closegraph();
}


