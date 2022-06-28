#pragma once
#include "general.h"
#include "player.h"
#include "coordination.h"

class Neighbor
{
public:
	Neighbor(int value, int R);
	inline void clearNeighbor(int, int);
	void neighborOut(int range);
	void testNeighbor(crd lastMove)const;
	inline void clearNeighborDanger();
	inline bool evaluateDanger();
	crd lastMoves[3][11];
	//row 0:buffer.
	//row 1 color1.
	//row 2.color 2.
	//[color][10].x ==Áô´æ·ÇÁã¸öÊý¡£

	void lastMoveStorage(int color, crd lastMove);

	crd nextMove(crd here);

	friend void YNInput(const char* notion, char A, char B);
	friend player;

private:
	int neighborArray[5][21];
	int neighborDanger[4][21];

#ifndef DEBUG
	//friend chessboard;
public:
#endif // !DEBUG
	int range;
	//number: directions v[0] to v[7];
	//data  : [0][0]==worst direction i : there are the most numbers of same color stones on direction: on ¡Àv[i],
	//        [0][1]==number of same color stones on worst direction.
	//        if range==5, [1][0]~[1][10]: detail information of this worst direction. (x,y) ¡À k v[i].  k¡Ê{-5,...0,...5};
	//        range¡Ê{1£¬...,10}
};

const struct badformat//0: empty   1: my color( !=empty && !=the other color )
{
	const int liveFour[5][5] = { {0,1,1,1,1},{1,0,1,1,1 },{1,1,0,1,1},{1,1,1,0,1},{1,1,1,1,0} };
	const int liveThree[5][5] = { {0,1,1,1,0},{1,0,1,1,0},{0,1,1,0,1},{1,0,1,0,1},{0,0,1,1,1} };

}bad;
const enum dangerType
{
	liveFour = 999,
	liveThree = 100
};
const enum MeOrEnemy
{
	me = true,
	enemy = false
};
