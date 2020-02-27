#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;
int sudoku[9][9] = { {0,0,5,3,0,0,0,0,0},{8,0,0,0,0,0,0,2,0},{0,7,0,0,1,0,5,0,0},{4,0,0,0,0,5,3,0,0},{0,1,0,0,7,0,0,0,6},{0,0,3,2,0,0,0,8,0},{0,6,0,5,0,0,0,0,9},{0,0,4,0,0,0,0,3,0},{0,0,0,0,0,9,7,0,0} };
int last1;
int findexr;
string temp;
vector<int>::iterator it;
void clears(int *num)
{
	for (unsigned int i = 0; i < 10; i++)
	{
		num[i] = 0;
	}
}
void vecdel(vector<int> &psolve, int &num)
{
	for (it = psolve.begin(); it != psolve.end();)
	{
		if (*it == num) {
			it = psolve.erase(it);
			return;
		}
		else
			++it;
	}
}
bool vecfnd(vector<int> &psolve, int &num)
{
	for (it = psolve.begin(); it != psolve.end();)
	{
		if (*it == num)
			return true;
		else
			++it;
	}
	return false;
}
void print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int i2 = 0; i2 < 9; i2++)
		{
			cout << sudoku[i][i2] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
class Point
{
public:
	Point(int y, int x)
	{
		ivalue = &(sudoku[y][x]);
		this->y = y;
		this->x = x;
		xphase = x / 3;
		yphase = y / 3;
		phase = yphase * 3 + xphase;
		for (int i = 1; i < 10; i++)
		{
			psolve.push_back(i);
		}
		for (int ix = 0; ix < 9; ix++)
		{
			if (sudoku[y][ix] != 0)
			{
				vecdel(psolve, sudoku[y][ix]);
			}
		}
		for (int iy = 0; iy < 9; iy++)
		{
			if (sudoku[iy][x] != 0)
			{
				vecdel(psolve, sudoku[iy][x]);
			}
		}
		int ixmin = xphase * 3;
		int ixmax = ixmin + 3;
		int iymin = yphase * 3;
		int iymax = iymin + 3;
		for (int iy = iymin; iy < iymax; iy++)
		{
			for (int ix = ixmin; ix < ixmax; ix++)
			{
				if (sudoku[iy][ix] != 0)
				{
					vecdel(psolve, sudoku[iy][ix]);
				}
			}
		}
	}
	int y;
	int x;
	int *ivalue;
	int xphase;
	int yphase;
	int phase;
	vector<int> psolve;
};
vector<Point> points;
void guess()
{
	vector<Point> xpoint[9];
	vector<Point> ypoint[9];
	vector<Point> ppoint[9];
	int num[10] = { 0 };
	for (auto v : points)
	{
		xpoint[v.x].push_back(v);
		ypoint[v.y].push_back(v);
		ppoint[v.phase].push_back(v);
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int i2 = 0; i2 < xpoint[i].size(); i2++)
		{
			for (unsigned int i3 = 0; i3 < xpoint[i][i2].psolve.size(); i3++)
			{
				++(num[xpoint[i][i2].psolve.at(i3)]);
			}
		}
		for (int i4 = 1; i4 < 10; i4++)
		{
			if (num[i4] == 1)
			{
				for (unsigned int i5 = 0; i5 < xpoint[i].size(); i5++)
				{
					if (vecfnd(xpoint[i][i5].psolve, i4))
					{
						*(xpoint[i][i5].ivalue) = i4;
					}
				}
			}
		}
		clears(num);
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int i2 = 0; i2 < ypoint[i].size(); i2++)
		{
			for (unsigned int i3 = 0; i3 < ypoint[i][i2].psolve.size(); i3++)
			{
				++(num[ypoint[i][i2].psolve.at(i3)]);
			}
		}
		for (int i4 = 1; i4 < 10; i4++)
		{
			if (num[i4] == 1)
			{
				for (unsigned int i5 = 0; i5 < ypoint[i].size(); i5++)
				{
					if (vecfnd(ypoint[i][i5].psolve, i4))
					{
						*(ypoint[i][i5].ivalue) = i4;
					}
				}
			}
		}
		clears(num);
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int i2 = 0; i2 < ppoint[i].size(); i2++)
		{
			for (unsigned int i3 = 0; i3 < ppoint[i][i2].psolve.size(); i3++)
			{
				++(num[ppoint[i][i2].psolve.at(i3)]);
			}
		}
		for (int i4 = 1; i4 < 10; i4++)
		{
			if (num[i4] == 1)
			{
				for (unsigned int i5 = 0; i5 < ppoint[i].size(); i5++)
				{
					if (vecfnd(ppoint[i][i5].psolve, i4))
					{
						*(ppoint[i][i5].ivalue) = i4;
					}
				}
			}
		}
		clears(num);
	}
}
void reset(int &index)
{
	int y, x;
	for (int i10 = index + 1; i10 <= last1; i10++)
	{
		y = points[i10].y;
		x = points[i10].x;
		if ((y == points[index].y) || (x == points[index].x) || (points[index].phase == points[i10].phase))
		{
			points[i10].psolve.clear();
			for (int i = 1; i < 10; i++)
			{
				points[i10].psolve.push_back(i);
			}
			for (int ix = 0; ix < 9; ix++)
			{
				if (sudoku[y][ix] != 0)
				{
					vecdel(points[i10].psolve, sudoku[y][ix]);
				}
			}
			for (int iy = 0; iy < 9; iy++)
			{
				if (sudoku[iy][x] != 0)
				{
					vecdel(points[i10].psolve, sudoku[iy][x]);
				}
			}
			int ixmin = points[i10].xphase * 3;
			int ixmax = ixmin + 3;
			int iymin = points[i10].yphase * 3;
			int iymax = iymin + 3;
			for (int iy = iymin; iy < iymax; iy++)
			{
				for (int ix = ixmin; ix < ixmax; ix++)
				{
					if (sudoku[iy][ix] != 0)
					{
						vecdel(points[i10].psolve, sudoku[iy][ix]);
					}
				}
			}
		}
	}
}
int indexr(vector<int> &psolve, int &num)
{
	for (unsigned int i = 0; i < psolve.size(); i++)
		if (psolve[i] == num)
			return i;
}
void solve(int &index);
void next1(int &index);
void solve(int &index)
{
	if (points[index].psolve.size() != 0)
	{
		*(points[index].ivalue) = points[index].psolve[0];
		reset(index);
		++index;
		if (index == last1)
			return;
		solve(index);
	}
	else
	{
		next1(--index);
	}
}
void next1(int &index)
{
	findexr = indexr(points[index].psolve, *(points[index].ivalue));
	if (findexr != points[index].psolve.size() - 1)
	{
		*(points[index].ivalue) = points[index].psolve[findexr + 1];
		reset(index);
		solve(++index);
	}
	else
	{
		*(points[index].ivalue) = 0;
		reset(index);
		next1(--index);
	}
}
int main()
{
	cout << "用0代表空位\n";
	for (int i = 0; i < 9; i++)
	{
		cout << "第" << i + 1 << "行:";
		cin >> temp;
		for (int i2 = 0; i2 < 9; i2++)
		{
			sudoku[i][i2] = temp[i2] - 48;
		}
	}
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (sudoku[y][x] == 0)
			{
				points.push_back(Point(y, x));
			}
		}
	}
	cout << "谜题:\n";
	print();
	guess();
	points.clear();
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (sudoku[y][x] == 0)
			{
				points.push_back(Point(y, x));
			}
		}
	}
	last1 = points.size();
	if (points.size() == 0){}
	else {
		int index = 0;
		solve(index);
	}
	cout << "答案:\n";
	print();
	cout << "完成!" << "\n";
	system("pause");
	return 0;
}