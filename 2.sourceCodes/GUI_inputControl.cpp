#include "Gui_inputControl.h"
#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"
#include "GUI_outputControl.h"
#include "GUI_button.h"

int testMouseAndKey()
{   //define a message object to record the message input by the user, from the keyboard/the mouse.
	//******You can see that " m. "shows a lot of input information.you can use them one by one.
	ExMessage m;

	while (true)
	{
		//get a message fromw the mouse and key.
		m = getmessage(EM_MOUSE | EM_KEY);

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			// if the mouse is moving, then put a red pixel(dot) at (x,y)
			putpixel(m.x, m.y, RED);
			break;

		case WM_LBUTTONDOWN:
			// if cliced left button down and you pressed contrl
			if (m.ctrl)
				//then we will write a big rectange.(+-10)
				rectangle(m.x - 10, m.y - 10, m.x + 10, m.y + 10);

			else
				// if you just clicked left button down 
				//then we will simply draw a small rectangle.
				rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			break;

		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)//if you pressed ESC the we will end this game.
				return 0;
		}
	}
}




void InputText(string* textReceiver,int lineNumber)
{
	cin.clear();
	directive.clear();

	setfillcolor(BLACK);
	setlinecolor(BLACK);

	fillrectangle(0, 390 + 40 * lineNumber, 10000, 425 + 40 * lineNumber);

	setfillcolor(BLACK);
	setlinecolor(RGB(255, 0, 255));

	line(300, 433 + 40 * lineNumber, 1000, 433 + 40 * lineNumber);
	string textBuffer = " ";
	char charBuffer;
	while ((charBuffer = _getch()) != '\r') //Stop displaying input info when ENTER is pressed 
	{
		if (charBuffer == '\b') //If the user input BACKSPACE,then we will cut a char fromt the tail and re-display it.
		{
			textBuffer = textBuffer.substr(0, textBuffer.size() - 1);
			setfillcolor(BLACK);
			setlinecolor(BLACK);

			fillrectangle(0, 390 + 40 * lineNumber, 10000, 425 + 40 * lineNumber);
		}
		else
		{
			textBuffer += (int)charBuffer;
		}
		setfillcolor(BLACK);
		setlinecolor(BLACK);

		fillrectangle(0, 390 + 40 * lineNumber, 10000, 425 +40*lineNumber);
		quickOutput(textBuffer.c_str(), middleLineX - textBuffer.length() / 2 * 10, 390+40*lineNumber, 255, 0, 255);
	}
	setfillcolor(BLACK);
	setlinecolor(BLACK);

	fillrectangle(0, 390 + 40 * lineNumber, 10000, 425 + 40 * lineNumber);


	if (textBuffer[0] == ' ')
		*textReceiver = textBuffer.substr(1, textBuffer.length());
	else
		*textReceiver = textBuffer;
}

//
//void implementWhileDetecting(void (*functionOne)(),void(*functionTwo)())
//{
//	bool hasClickedButton = false;
//	ExMessage mouse;
//	string temp = " ";
//	while (true)
//	{
//		mouse = getmessage(EM_MOUSE);
//		if (mouse.message == WM_LBUTTONDOWN)
//		{
//			if (buttonSkip.hasClicked() == true)
//			{
//				buttonSkip.responseSkip(temp);
//				hasClickedButton = true;
//			}
//			if (hasClickedButton == false)
//			{
//				functionOne();
//				functionTwo();
//			}
//		}
//	}
//}