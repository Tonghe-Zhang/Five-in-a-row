#include "COMMUNICATION.h"
#include "GUI_button.h"
#include "player.h"
#include "GUI_inputControl.h"


using namespace std;

string communicator::IPaddress = "127.0.0.1";

void communicator::changeGameboard(char* buffer)
{
	//Let player change gameboard, and communicator will be only in charge of recording it .
	Gui.integratedOutputInstructions(GUI::showPlayerTurn);
	Player[gameboard.player_s_turn].setchess();
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(300, 0, 1000, 50);
	updateOriginToShrink();
	MatrixToArray(gameboardShrink, gameboardArray);
	ArrayToChar(this->gameboardArray, buffer);
}
void communicator::getServerIP(bool isMe)
{
	if (isMe)
	{
		communicator::IPaddress = "127.0.0.1";
		quickOutput("Your friend needs your IP.Press WIN and type in 'cmd ' ,'ipconfig' to find out", "line", -1);
		quickOutput("Press any key to continue after telling him/her.", "line", 0);
		system("pause");
		cleardevice();
		return;
	}
	cleardevice();
	quickOutput("Please type in your  friend's IP.", "line", 0);
	InputText(&communicator::IPaddress);
	cleardevice();
}
void communicator::showMatrix(int data[16][16])
{

	gameboard.display();
}


//Parameter: none.
//Return Value:  1 "Client terminated dialogue."
//              -1  "WASStartup failed !";
//              -2  "socket failed 
//              -3  "bind failed !";
//              -4:  "listen failed !" 
//              -5 "accept failed !" 
//              -6  "recv failed !"
//              -7 "send failed !" 
int communicator::ServerToClient()
{

	WSADATA wsd;         //WSADATA变量，用于初始化Windows Socket 
	SOCKET sServer;     //服务器socket，用于监听客户端请求
	SOCKET sClient;     //客户端socket，用于实现与客户端的通信
	int retVal;         //调用各种socket函数的返回值
	char buf[BUF_SIZE];

	quickOutput("Please wait for your friend to operate.");

	//****************************************************************************************************************************************
	Sleep(2000);

	//****************************************************************************************************************************************

		//初始化Socket环境
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{

		return -1;
	}

	//创建用于监听的Socket
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{

		return -2;
	}

	//设置服务器Socket地址
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(9990);
	addrServ.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	//绑定Sockets Server 到本地地址
	retVal = bind(sServer, (const struct sockaddr*)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{

		closesocket(sServer);
		WSACleanup();
		return -3;
	}
	//在Socket Server上进行监听
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{

		closesocket(sServer);
		WSACleanup();
		return -4;
	}

	//****************************************************************************************************************************************

	quickOutput("If he/she has finished, Press any key to continue.");
	std::system("pause");
	cleardevice();
	gameboardPainter Painter(15);
	Painter.drawGameboard();
	Sleep(3000);
	gameboard.game_status = 0;
	//****************************************************************************************************************************************


		//接受来自客户端的请求
	std::cout << "TCP Server Start..." << std::endl;
	sockaddr_in addrClient;    //客户端地址
	int addrClientLen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*) & addrClient, &addrClientLen);
	if (INVALID_SOCKET == sClient)
	{

		closesocket(sServer);
		WSACleanup();
		return -5;
	}

	//在服务器与客户端之间发送和接收数据

	//循环接受客户端的数据，直接客户端发送quit命令后退出
	while (gameboard.game_status != 225 && gameboard.game_status != -1 && gameboard.game_status != -2)
	{

		//Show buttons at which this game just started.
		Button* ptr[6] = { &buttonRename,&buttonRetract,&buttonWithdraw,&buttonScore,&buttonQuit,&buttonSkip };


		memset(buf, 0, BUF_SIZE);
		retVal = recv(sClient, buf, BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{

			closesocket(sServer);
			WSACleanup();
			return -6;
		}
	
		//*********************************************************************************************************************
		//std::cout << "\nReceive from Client: \n\t";
		int b[MAXn] = { 0 }, temp = -1, newStatus = 0;
		for (int i = 0; i < strlen(buf); i++)
		{
			temp = (int)buf[i] - 1;
			b[i] = (temp < 0 ? temp + 256 : temp);
		}
		ArrayToMatrix(b, gameboardShrink);
		updateShrinkToOrigin();

		//Check gameboard changes.
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
			{
				if (gameboardShrink[i][j] != chessColor::empty)
					newStatus++;
			}
		//Set
		if (newStatus == gameboard.game_status + 1)
		{

			showMatrix(gameboard.board);
			gameboard.operator++();//Change gameboard.player_s_turn.
			gameboard.game_status++;//Add total stone number.
		}
		//Withdraw 
		else if (newStatus == gameboard.game_status - 1)
		{

			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillrectangle(300, 40, 1000, bottomBoarderY);


			Painter.drawGameboard();
			showMatrix(gameboard.board);
			//gameboard.operator++();//Change gameboard.player_s_turn.
			gameboard.game_status--;//decrease total stone number.
		}
		//Retract
		else if (newStatus == gameboard.game_status - 2)
		{

			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillrectangle(300, 40, 1000, bottomBoarderY);


			Painter.drawGameboard();
			showMatrix(gameboard.board);
			//gameboard.operator++();//Change gameboard.player_s_turn.
			gameboard.operator++();
			gameboard.game_status -= 2;//decrease total stone number by 2.
		}

		//*********************************************************************************************************************


		//如果客户端发送“quit”字符串，则服务器退出
		if (strcmp(buf, "quit") == 0)
		{
			retVal = send(sClient, "quit", strlen("quit"), 0);
			break;
		}
		//*********************************************************************************************************************

		//否则向客户端发送回字符串
		else
		{
			changeGameboard(buf);

			retVal = send(sClient, buf, strlen(buf), 0);

			if (SOCKET_ERROR == retVal)
			{

				closesocket(sServer);
				closesocket(sClient);
				WSACleanup();
				return -7;
			}
		}
	//*********************************************************************************************************************

	}

	//释放资源
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();

	std::system("pause");
	return 1;
}


int communicator::ClientToServer()
{
	WSADATA wsd;   //用于初始化Windows socket
	SOCKET sHost;   //与服务器进行通信的socket
	SOCKADDR_IN servAddr;  //服务器地址
	char buf[BUF_SIZE];   //用于接收数据缓冲区
	int retVal;    //调用各种Socket函数的返回值


	cleardevice();
	quickOutput("Press any key to continue.");
	std::system("pause");
	cleardevice();
	gameboardPainter Painter(15);
	Painter.drawGameboard();
	
	//初始化socket动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed !" << endl;
		return -1;
	}
	//创建用于通信的socket
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		cout << "socket failed !" << endl;
		WSACleanup();;
		return -2;
	}

	//Classical Triple initialization for socket.
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr(communicator::IPaddress.c_str());
	servAddr.sin_port = htons(9990);
	int sServerAddrlen = sizeof(servAddr);
	//连接到服务器
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed !" << endl;
		closesocket(sHost);
		WSACleanup();
		return -8;
	}

	//在客户端与服务器之间发送和接收数据
	while (gameboard.game_status != 225 && gameboard.game_status != -1 && gameboard.game_status != -2)
	{

		//*********************************************************************************************************************************
		//ASCII中只有0~127  且写入0可能有问题，因此我们把0~256映射成 1~127+

		changeGameboard(buf);

		//向服务器发送数据
		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			//std::cout << "send failed !" << std::endl;
			closesocket(sHost);
			WSACleanup();
			return -7;
		}

		//*********************************************************************************************************************************

		//接收服务器回传的数据
		retVal = recv(sHost, buf, sizeof(buf) + 1, 0);


		int b[MAXn] = { 0 }, temp = -1, newStatus = 0;
		for (int i = 0; i < strlen(buf); i++)
		{
			temp = (int)buf[i] - 1;
			b[i] = (temp < 0 ? temp + 256 : temp);
		}
		ArrayToMatrix(b, gameboardShrink);
		updateShrinkToOrigin();
		showMatrix(gameboard.board);

		//Check gameboard changes.
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
			{
				if (gameboardShrink[i][j] != chessColor::empty)
					newStatus++;
			}
		//Set
		if (newStatus == gameboard.game_status + 1)
		{

			showMatrix(gameboard.board);
			gameboard.operator++();//Change gameboard.player_s_turn.
			gameboard.game_status++;//Add total stone number.
		}
		//Withdraw 
		else if (newStatus == gameboard.game_status - 1)
		{

			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillrectangle(300, 40, 1000, bottomBoarderY);
			Painter.drawGameboard();
			showMatrix(gameboard.board);
			//gameboard.operator++();//Change gameboard.player_s_turn.
			gameboard.game_status--;//decrease total stone number.
		}
		//Retract
		else if (newStatus == gameboard.game_status - 2)
		{

			setfillcolor(BLACK);
			setlinecolor(BLACK);
			fillrectangle(300, 40, 1000, bottomBoarderY);


			Painter.drawGameboard();
			showMatrix(gameboard.board);
			gameboard.operator++();//Change gameboard.player_s_turn.
			//gameboard.operator++();
			gameboard.game_status -= 2;//decrease total stone number by 2.
		}

		//*********************************************************************************************************************************
		if (strcmp(buf, "quit") == 0)
		{
			std::cout << "quit!" << std::endl;
			break;
		}
	}
	//释放资源
	closesocket(sHost);
	WSACleanup();
	std::system("pause");
	return 0;
}

void communicator::updateShrinkToOrigin()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			gameboard.board[i + 1][j + 1] = gameboardShrink[i][j];
		}
}
void communicator::updateOriginToShrink()
{
	for (int i = 1; i < 16; i++)
		for (int j = 1; j < 16; j++)
		{
			this->gameboardShrink[i - 1][j - 1] = gameboard.board[i][j];
		}
}
void communicator::MatrixToArray(int source[15][15], int* destination)
{

	updateOriginToShrink();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			destination[i * 15 + j] = source[i][j];
		}
	}
}
void communicator::ArrayToMatrix(int* souce, int destination[15][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			destination[i][j] = souce[i * 15 + j];
		}
	}
	updateShrinkToOrigin();
}
void communicator::ChToMatrix(char* buf, int gameboardShrink[15][15])
{
	int temp = 0;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			temp = (int)buf[i * 15 + j];
			gameboardShrink[i][j] = (temp < 0 ? temp + 256 : temp);
		}
	updateShrinkToOrigin();
}
void communicator::ArrayToChar(int* gameboardArray, char* buffer)
{
	for (int i = 0; i < MAXn; i++)
	{
		buffer[i] = (char)(1 + gameboardArray[i]);
	}
	buffer[MAXn] = '\0';
}
void communicator::InitMatrix(int data[15][15])
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			data[i][j] = 0;
}
void communicator::communicate()
{
	int connectionSuccess = 0;
	if (isServer)
	{
		connectionSuccess = (this->ServerToClient());
		if (connectionSuccess == 1)
		{
			quickOutput("This is the end of the game!  Client terminated this dialogue.");
			Sleep(2500);
			return;
		}
	}
	else
	{
		connectionSuccess = (this->ClientToServer());
		if (connectionSuccess == 1)
		{
			quickOutput("This is the end of the game!  Server terminated this dialogue.");
			Sleep(2500);

			return;
		}
	}
	switch (connectionSuccess)
	{
	case -1:  quickOutput("WASStartup failed !");
		break;
	case -2:  quickOutput("socket failed.");
		break;
	case  -3:  quickOutput("bind failed !");
		break;
	case  -4:  quickOutput("listen failed !");
		break;
	case  -5:  quickOutput("accept failed !");
		break;
	case -6: quickOutput("recv failed !");
		break;
	case -7: quickOutput("This is the end of the game!");// "send failed !");
		break;
	case -8:quickOutput("Client to Server connection failed !");
		break;
	default:
		quickOutput("This is the end of the game!");
	}
	Sleep(2500);
	return;
}