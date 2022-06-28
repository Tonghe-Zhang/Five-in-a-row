#pragma once
#include "general.h"
#define MAXSTAR 1000

class STAR
{
private:
	double	x;
	int		y;
	double	step;
	int		color;

public:
	STAR(int i = 0);
	inline void InitStar(int i, int mode);
	inline void MoveStar(int i, int mode);
	static void showStarryNight();
};

extern STAR star[MAXSTAR];


