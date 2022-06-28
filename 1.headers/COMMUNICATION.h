#pragma once
#include "general.h"




//Link winsock library.
#pragma commet(lin,"Ws2_32.lib");

//STD console header files.
#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>

//SOCKET header files.
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>           //for file io

#include <iostream>
#include <stdlib.h>
#pragma comment (lib,"WS2_32.lib")

#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include "player.h"
#include "chessboard.h"

using namespace std;


using namespace std;

#define SCK_VERSION2 0x0202
//Char 中不能存储超过225个数据，至多分配225个bit给一个char的缓冲区。索引范围必须是0~
#define BUF_SIZE  226   //buf size must no less than n + 1
#define MAXn   225

class communicator
{
private:
	int gameboardArray[225];
	int gameboardShrink[15][15];
	bool isServer;
	void MatrixToArray(int source[15][15], int* destination);
	void ArrayToMatrix(int* souce, int destination[15][15]);
	void ChToMatrix(char* buf, int gameboardShrink[15][15]);
	void ArrayToChar(int* gameboardArray, char* buffer);
	void updateShrinkToOrigin();
	void updateOriginToShrink();
	void InitMatrix(int data[15][15]);
	//APIs:
	int ServerToClient();
	int ClientToServer();
	void showMatrix(int data[16][16]);
	void changeGameboard(char* buffer);

public:
	communicator(bool isServer) :isServer(isServer) { InitMatrix(gameboardShrink); };
	void communicate();
	static void getServerIP(bool isMe);
	static string IPaddress;
};



