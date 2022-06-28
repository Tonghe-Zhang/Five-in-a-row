#include "general.h"
#include "globalFunctionDeclaration.h"
#include "globalVariableDeclaration.h"
#include "Neighbor.h"
#include "chessboard.h"
#include "coordination.h"

//constructor

Neighbor::Neighbor(int value, int R)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 21; j++)
		{
			neighborArray[i][j] = value;
			if (i == 5)
			{
				continue;
			}
			neighborDanger[i][j] = 0;
		}

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			lastMoves[i][j].x = 0;
			lastMoves[i][j].y = 0;
		}

	}

	range = R;
}


inline void Neighbor::clearNeighborDanger()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			neighborDanger[i][j] = 0;
		}
	}
}



void Neighbor::lastMoveStorage(int color, crd lastMove)
{
	int n = (lastMoves[color][10].x);
	if (n < 10)
	{
		lastMoves[color][n] = lastMove;
		(lastMoves[color][10].x)++;
	}
	else
	{
		//记录满了之后会往前push压栈。
		for (int i = 1; i < 10; i++)
			lastMoves[0][i] = lastMoves[color][i];
		for (int i = 1; i < 10; i++)
			lastMoves[color][i - 1] = lastMoves[0][i];
		lastMoves[color][9] = lastMove;
	}


}


//clear row m to row M of  neighbor. 
//functions processing array int neighbor[2][10];
inline void Neighbor::clearNeighbor(int m = 0, int M = 1)
{
	for (int i = m; i < M + 1; i++)
		for (int j = 0; j < 21; j++)
			neighbor.neighborArray[i][j] = -1;
}

//display neighborArray.For debug.
void Neighbor::neighborOut(int range)//display neighbor[0][0]to[1][2*range+1]
{
	cout << "neighbor:";
	for (int i = 0; i < 5; i++)
	{
		printf("\n");
		for (int k = 0; k < 2 * range + 1; k++)
		{
			if (i < 5)
			{
				if (neighbor.neighborArray[i][k] == chessColor::empty)
					cout << "□";//empty
				else if (neighbor.neighborArray[i][k] == -1)
					cout << "D"; //different color.
				else if (neighbor.neighborArray[i][k] == 1)
					cout << "S";//same color.
				else if (neighbor.neighborArray[i][k] == -2)
					cout << "×";//out of range.
				else
					cout << neighbor.neighborArray[i][k];
			}
			else
			{
				cout << setw(2) << neighbor.neighborArray[i][k];
			}
		}

	}
	printf("\n");
}

//对于点lastMove:求出其八个方向中[-range, range]以内共2*range+1个同色子最多的一对方向
//以及该方向上的所有位置颜色分布(同色，异色，空，越界)
//存在neighborArray中.
void Neighbor::testNeighbor(crd lastMove) const
{
	neighbor.clearNeighbor();
	int x = lastMove.x;
	int y = lastMove.y;
	crd point(x, y);
	crd here = point;
	int sameColor = 0, myColor = gameboard.board[x][y], maxSameColor = 0, worstDirection = -1;


	//【【【【【【算法优化】】】】】//
	for (int i = 0; i < 4; i++)//Four directions.
	{
		/*	std::cout << "\n±v[" << i << "]: ";*/
		sameColor = 0;
		for (int j = -range; j < range + 1; j++)//2*range+1 places to be tested.
		{
			crd here = point + (j * v[i]);

			if ((!(here.x >= 1 && here.x <= 15 && here.y >= 1 && here.y <= 15)))// off the gameboard.
				neighbor.neighborArray[i][j + range] = -2;//off border.
			else
			{
				int color = gameboard.board[here.x][here.y];
				if (color == myColor)//same color.
				{
					neighbor.neighborArray[i][j + range] = 1;
					sameColor++;
				}
				else if (color == chessColor::empty)//empty
					neighbor.neighborArray[i][j + range] = 0;
				else//different color.
					neighbor.neighborArray[i][j + range] = -1;
			}

		}
		
	}
}

////考察是否有活四，有则将坐标k传给array[2],没有则为活三的眼建立危险权重，记录在danger中。从danger中取最大值作为最危险的地方，如果有多个则随机选一个。
//inline bool Neighbor::evaluateDanger() Old Version

inline bool Neighbor::evaluateDanger()
{

	int sub[5] = { 0 };
	
	for (int i = 0; i < 4; i++)
	{


		for (int k = 0; k < 2 * range + 1 - 4; k++)
		{
			getsubString(neighborArray[i], k, 5, sub);
			
			for (int j = 0; j < 5; j++)
			{
				if (equal(sub, bad.liveFour[j]))
				{

					neighborArray[4][1] = i;
					neighborArray[4][2] = k + j;
					return 1;
				}
			}

			if (equal(sub, bad.liveThree[0]))
			{
				neighborDanger[i][k]++;
				neighborDanger[i][k + 4]++;

			}
			else if (equal(sub, bad.liveThree[1]))
			{
				neighborDanger[i][k + 1]++;

			}
			else if (equal(sub, bad.liveThree[2]))
			{
				//活眼在  3号位。
				neighborDanger[i][k + 3]++;
			}
			else if (equal(sub, bad.liveThree[3]))
			{
				//活眼在 1 或 3号位。
				neighborDanger[i][k + 1]++;
				neighborDanger[i][k + 3]++;
			}
			else if (equal(sub, bad.liveThree[4]))
			{
				neighborDanger[i][k + 1]++;
			}
		}
	}
	return 0;
}
//根据对方玩家上一次下棋的位置，决断其八个方向中最危险的方向，然后从中决断最危险的点，传回来作为下一步下在哪里的建议。
// X：上一步位置  Y：建议下在哪里。
//这个算法的漏洞在于应该开一个8*21的array和danger数组，每个方向都decide一遍，最后从整个danger表中取最大。
//因为可能某个方向上子很多，但是都没啥威胁。另一些方向子少，但已经活四了。
//Old version crd Neighbor::nextMove(crd here)
crd Neighbor::nextMove(crd here)
{
	neighbor.testNeighbor(here);

	//clear.danger.
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			neighborDanger[i][j] = 0;
		}
	}
	//Next move on v[worst_direction],sequecne worst_sequence; 
	int worst_direction = 0, worst_sequence = 0;
	if (evaluateDanger())//==1:there is a liveFour.
	{
		worst_direction = neighborArray[4][1];
		worst_sequence = neighborArray[4][2];
	}
	else
	{
		//find the maximum  of neighborDanger at (I,J)
		int I = 0, J = 0;
		int maximumDanger = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				//cout << neighborDanger[m] << " ";
				if (neighborDanger[i][j] > maximumDanger)
				{
					I = i;
					J = j;
					maximumDanger = neighborDanger[i][j];

				}
			}
		}
		//最大值的总数为maxNumber个，都存在choice中。  choice ,[0]存储第几个方向v[i]的i； [1]存储第几个：k
		//cout << "\nmaximumDanger==" << maximumDanger << "\n";
		int choice[2][10] = { 0 }, maxNumber = 0;
		//If all the points are safe,then you can attack freely.//如果全都安全，则返回here本地值，这是一个不可能下子的建议——意味着没有危险，你可以进攻。
		if (maximumDanger == 0)
		{
			return here;

		}
		//else, you have to block the other chesser.

		else
		{
			//求解所有最大值点，并将其方向i与序列k存在choice[2][10]中。
			//find all the maximum points, record them in [i][j].  [i]==v[i],direction; [j]==k, sequence;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 21; j++)
				{
					if (neighborDanger[i][j] == maximumDanger)
					{
						choice[0][maxNumber] = i;
						choice[1][maxNumber] = j;
						maxNumber++;
					}
				}
			}
			//最大值不唯一时随机选取一个。
			if (maxNumber > 1)
			{
				//产生随机实数然后均匀概率地压缩到整数域上{0,1,2...},产生一个随机整型值randomValue，是choice的一个列标。
				std::default_random_engine F;
				std::uniform_real_distribution<double> f(1, maxNumber * 50 - 1);
				F.seed(time(NULL));
				int randomValue = (int)(f(F) / 50);

				worst_direction = choice[0][randomValue];
				worst_sequence = choice[1][randomValue];
				neighborArray[4][1] = worst_direction;
				neighborArray[4][2] = worst_direction;


			}
			else
			{
				worst_sequence = choice[1][0];
				worst_direction = choice[0][0];

			}
		}

	}
	crd temp = (worst_sequence - range) * v[worst_direction];
	crd result = here + temp;
	return result;
}