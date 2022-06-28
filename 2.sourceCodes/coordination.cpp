#include "chessboard.h"
#include "coordination.h"
#include "globalVariableDeclaration.h"

//For class coordination
crd operator+(crd& c1, crd& c2)
{
	crd temp;
	temp.x = c1.x + c2.x;
	temp.y = c1.y + c2.y;
	return temp;
}

crd operator-(crd& c1, crd& c2)
{
	crd temp;
	temp.x = c1.x - c2.x;
	temp.y = c1.y - c2.y;
	return temp;
}

void crd::operator=(const crd& origin)
{
	this->x = origin.x;
	this->y = origin.y;
}

crd& operator *(int k, crd C)
{
	buffer.x = k * C.x;
	buffer.y = k * C.y;
	return buffer;
}


bool operator==(crd& c1, crd& c2)
{
	return ((c1.x == c2.x) && (c1.y == c2.y));
}


int crd::color()
{
	return gameboard.board[x][y];
}


ostream& operator<<(ostream& cout, crd c)
{
	cout << "(" << setw(2) << c.x << "," << setw(2) << c.y << ")  ";
	return cout;
}