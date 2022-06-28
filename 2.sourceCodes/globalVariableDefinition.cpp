#include"general.h"
#include "chessboard.h"
#include "coordination.h"

#include "fileManagement.h"

#include "Neighbor.h"
#include "player.h"

#include "GUI_backgroundStarryNight.h"
#include "GUI_outputControl.h"

#include "GUI_button.h"

string directive = " ";
string name1 = " ";
string name2 = " ";
string filename = { "Gameboard00.txt" };
int play_times = 0;
crd positition;
crd buffer(0, 0);
int X = 0;
int Y = 0;
crd v[4] = { crd(1,0),crd(1,1),crd(0,1),crd(-1,1) };
//four constant unit vectors indicates four directions: south, southeast, east ,northeast.
//v[0]: ¡ý   //v[1]: ¨K    //v[2]: ¡ú   //v[3]: ¨J
// ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ú y(column)
// |             |
// |        ¨I  ¡ü    ¨J
// |         [6][7]|[3]
// |------¡û[5](x,y)[2]¡ú     
// |         [4][0][1]
// |        ¨L  ¡ý    ¨K
// |
// ¡ýx (row) 

chessboard gameboard(0, 1);

Neighbor neighbor(100, 5);

player Player[3] = { player(chessColor::empty),player(black),player(white) };

fileManager fileKeeper('0');


int pictureWidthX = 6400;
int pictureWidthY = 4800;

int GUI_mode = start;
bool playAgain = true;
//This game will not end in a default situation.
bool isWithHuman = true;
//With computer or with friend. computer, false; friend,true;
bool isUsingNet = false;
//Using IPV4 or not. 




STAR star[MAXSTAR];
GUI Gui(1);

int gameboardPainter::deltaY = gameboardPainter::leftReferencePoints[1].y - gameboardPainter::leftReferencePoints[0].y;

crd gameboardPainter::bottomeReferencePoints[20];
crd gameboardPainter::upperReferencePoints[20];
crd gameboardPainter::leftReferencePoints[20];
crd gameboardPainter::rightReferencePoints[20];
const int gameboardPainter::gameboardScale = 15;

crd clickPosition(0, 0);

Button* player::ptr[6] = { &buttonRename,&buttonRetract,&buttonWithdraw,&buttonScore,&buttonQuit,&buttonSkip };
void (*player::fun[6])(string) = { Button::responseRename,Button::responseRetract,Button::responseWithdraw, Button::responseScore,Button::responseQuit,Button::responseSkip };