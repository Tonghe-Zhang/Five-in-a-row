#pragma once
#include "general.h"


class crd
{
public:
	crd(int X = 0, int Y = 0) :x(X), y(Y) {};
	//crd=crd;  crd==color, crd!=color;
	void operator=(const crd& origin);
	void changeCoordination(int newX, int newY) { x = newX; y = newY; }
	int color();
	//linear operators.
	friend  crd operator+(crd& c1, crd& c2);
	friend  crd operator-(crd& c1, crd& c2);
	friend  crd& operator *(int k, crd C);
	friend  bool operator==(crd&, crd&);
	friend  ostream& operator<<(ostream& cout, crd c);

	int x;
	int y;
};//crd==coordination
extern crd v[4];
//four constant unit vectors indicates four directions: south, southeast, east ,northeast.
//v[0]: ¡ý   //v[1]: ¨K    //v[2]: ¡ú   //v[3]: ¨J
// ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ú y(column)
// |             |
// |             |
// |             |[3]¨J
// |-----------(x,y)[2]¡ú     
// |              [1]¨K
// |            [0]¡ý
// |
// ¡ýx (row) 
extern crd positition;
//to store the position on which the last stone was set.