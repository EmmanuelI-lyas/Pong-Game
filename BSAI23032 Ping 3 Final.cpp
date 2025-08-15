#include <iostream>
#include <Windows.h>
#include <conio.h>
#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
using namespace std;
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}

void drawball(int ox, int oy, char b)
{
	SetClr(15, 0);
	gotoRowCol(ox, oy - 1);
	cout << b;
	gotoRowCol(ox, oy);
	cout << b;
}
void initial_paddles(int p1x, int p1y, char b, int p2x, int p2y)
{
	for (int i = 0; i < 3; i++, p1x++)
	{
		gotoRowCol(p1x, p1y);
		cout << b;
	}
	for (int i = 0; i < 3; i++, p2x++)
	{
		gotoRowCol(p2x, p2y);
		cout << b;
	}
}
void draw1(int px, int py, char b)
{
	SetClr(9, 0);
	for (int i = 0; i < 7; i++, px++)
	{
		gotoRowCol(px, py);
		cout << b;
	}
}
void draw2(int jx, int jy, char b)
{
	SetClr(4, 0);
	for (int i = 0; i < 7; i++, jx++)
	{
		gotoRowCol(jx, jy);
		cout << b;
	}
}
void initial_ball(int ox, int oy, char b)
{
	drawball(ox, oy, b);
}
void remove_ball(int& ox, int& oy, char d)
{
	gotoRowCol(ox, oy - 1);
	cout << d;
	gotoRowCol(ox, oy);
	cout << d;
}
void rem_Paddle1(int p1x, int p1y, char d)
{
	for (int i = 0; i < 7; i++, p1x++)
	{
		gotoRowCol(p1x, p1y);
		cout << d;
	}
}
void moveball(int& ox, int& oy, char c)
{
	if (c == 'r')
	{
		oy++;
	}
	else if (c == 'l')
	{
		oy--;
	}
	else if (c == '1')
	{
		ox++;
		oy++;
	}
	else if (c == '2')
	{
		ox--;
		oy++;
	}
	else if (c == '3')
	{
		ox--;
		oy--;
	}
	else if (c == '4')
	{
		ox++;
		oy--;
	}

}
void move_paddle(int& px, int py, int& jx, int jy, char d, char b)
{
	char o;
	if (_kbhit())
	{
		o = _getch();
		switch (o)
		{
		case'W':
		case 'w':
		{
			rem_Paddle1(px, py, d);
			if (px - 1 > 0)
			{
				px = px - 1;
			}
			draw1(px, py, b);
			break;
		}
		case'S':
		case's':
		{
			rem_Paddle1(px, py, d);
			if (px + 7 <= 28)
			{
				px = px + 1;
			}
			draw1(px, py, b);
			break;
		}
		case 72:
		{
			rem_Paddle1(jx, jy, d);
			if (jx - 1 > 0)
			{
				jx = jx - 1;
			}
			draw2(jx, jy, b);
			break;
		}
		case 80:
		{
			rem_Paddle1(jx, jy, d);
			if (jx + 7 <= 28)
			{
				jx = jx + 1;
			}
			draw2(jx, jy, b);
			break;
		}
		}
	}
}
void boundary_bounce(int& ox, int& oy, char& c, int& px, int py,int& s1,int& s2
)
{
	if (c == 'r' && oy == 84)
	{
		s1++;
		ox = 14;
		oy = 40;
		c = 'l';
	}
	else if (c == 'l' && oy == 2)
	{
		s2++;
		ox=14;
		oy = 40;
		c = 'r';
	}
	else if (c == '1' && ox == 28)
	{
		c = '2';
	}
	else if (c == '1' && oy == 84)
	{
		c = '3';
	}
	else if (c == '2' && ox == 1)
	{
		c = '1';
	}
	else if (c == '2' && oy == 84)
	{
		s1++;
		ox = 14;
		oy = 40;
		c = 'l';
	}
	else if (c == '3' && ox == 1)
	{
		c = '4';
	}
	else if (c == '3' && oy == 2)
	{
		s2++;
		ox = 14;
		oy = 40;
		c = 'r';
	}
	else if (c == '4' && ox == 28)
	{
		c = '3';
	}
	else if (c == '4' && oy == 2)
	{
		s2++;
		ox = 14;
		oy = 40;
		c = 'r';
	}

}
void ballcol1(int px, int& oy, int py, int& ox, char& c)
{
	if (py + 1 == oy - 1)
	{
		if (px == ox || px + 1 == ox)
		{
			c = '1';
		}
		else if (px + 2 == ox || px + 3 == ox)
		{
			c = 'r';
		}
		else if (px + 4 == ox || px + 5 == ox)
		{
			c = '2';
		}
	}
}
void ballcol2(int jx, int& oy, int jy, int& ox, char& c)
{
	if (jy == oy + 1)
	{
		if (jx == ox || jx + 1 == ox)
		{
			c = '3';
		}
		else if (jx + 2 == ox || jx + 3 == ox)
		{
			c = 'l';
		}
		else if (jx + 4 == ox || jx + 5 == ox)
		{
			c = '4';
		}
	}
}
void diff(int& s, char sel)
{
	switch (sel)
	{
	 case 'E':
	 case 'e':
	 {
		 s = 60;
		break;
	 }
	 case 'M':
	 case 'm':
	 {
		 s = 50;
		 break;
	 }
	 case 'H':
	 case 'h':
	 {
		 s = 40;
		 break;
	 }
	 case 'P':
	 case'p':
	 {
		 s = 20;
		 break;
	 }
	}

}

void score(int s1, int s2)
{
	gotoRowCol(3, 32);
	SetClr(9, 0);
	cout << "Player1 ";
	SetClr(15, 0);
	cout << "  :  ";
	SetClr(4, 0);
	cout << "Player2 ";
	gotoRowCol(4, 34);
	SetClr(9, 0);
	cout << s1;
	cout << "            ";
	SetClr(4, 0);
	cout<< s2;
}
bool gamewin(int ls, int s1, int s2)
{
	if (s1 == ls)
	{
		return true;
	}
	if (s2 == ls)
	{
		return true;
	}
	return false;
}
void draw_boundaries(int lx, int ly, char a)
{
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < ly; j++)
		{
			gotoRowCol(i, j);
			cout << a;
		}
	}
	for (int i = 0; i < lx; i++)
	{
		for (int j = 0; j < lx; j++)
		{
			int k = 0, m = ly;
			SetClr(4, 0);
			gotoRowCol(i, k);
			cout << a;
			SetClr(9, 0);
			gotoRowCol(i, m);
			cout << a;
		}
	}
	for (int i = lx - 1; i < lx; i++)
	{
		for (int j = 0; j < ly + 1; j++)
		{
			SetClr(15, 0);
			gotoRowCol(i, j);
			cout << a;
		}
	}


}
void gameplay()
{
	char  a = -37, b = -37, d = 32, c = 'r', sel, sel1;
	int lx = 30, ly = 85, ox = 15, oy = 40, px = 14, py = 3, jx = 14, jy = 82;
	int s = 60, s1 = 0, s2 = 0, ls, lsh;
	SetClr(15, 0);
	cout << "Please Enter Difficulty" << endl << " E for Easy" << endl << " M for Moderate" << endl
		<< " H for Hard " << endl << " P for Pro" << endl;
	cin >> sel;
	sel1 = sel;
	cout << endl;
	SetClr(15, 0);
	cout << "Please enter the Winning Score for the Game" << endl;
	cout << endl;
	cin >> ls;
	lsh = ls;
	system("cls");
	diff(s, sel1);
	draw_boundaries(lx, ly, a);
	initial_ball(ox, oy, b);
	draw1(px, py, b);
	draw2(jx, jy, b);
	while (!gamewin(lsh, s1, s2))
	{
		remove_ball(ox, oy, d);
		moveball(ox, oy, c);
		boundary_bounce(ox, oy, c, px, py, s1, s2);
		move_paddle(px, py, jx, jy, d, b);
		ballcol1(px, oy, py, ox, c);
		ballcol2(jx, oy, jy, ox, c);
		drawball(ox, oy, a);
		score(s1, s2);
		gotoRowCol(lx + 2, ly + 2);
		Sleep(s);
	}
	if (s1 == lsh)
	{
		SetClr(9, 0);
		gotoRowCol(14, 36);
		cout << "Player One won";
	}
	else if (s2 == lsh)
	{
		SetClr(4, 0);
		gotoRowCol(14, 36);
		cout << "Player two Won";
	}
	gotoRowCol(lx + 3, ly + 3);
}
int main()
{
	int lix = 45, liy = 90;
	char m,f;
	do
	{
		gameplay();
		Sleep(1500);
		system("cls");
		SetClr(15, 0);
		gotoRowCol(lix + 2, liy + 5);
		cout << "Do you want to restart game ? "<<endl;
		cout << "Y for yes"<<endl;
		cout << "N for no and exit from game" << endl;
		cin >> f;
		m = f;
		system("cls");
		if (m != 'y' || m != 'Y')
		{
			cout << "You Exited Game ";
		}
	} 
	while (m=='y'||m=='Y');
	gotoRowCol(lix + 2, liy + 5);
	return 0;
}