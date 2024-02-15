#include <bits/stdc++.h>
#include <windows.h>
#include <graphics.h>
using namespace std;

int velx = 0, vely = 0, friction = 2, test = 0, factor;
POINT pos, prev;
bool game = true;
class Ball
{
	public:
		int x, y, r = 20;
		void Reset(int X, int Y)
		{
			x = X;
			y = Y;
		}
		void Draww()
		{
			velx = min(velx, 30);
			velx = max(velx, -30);
			vely = min(vely, 30);
			vely = max(vely, -30);
			x += (velx * 7)/10;
			y += (vely * 7)/10;
			if(test == 0)
			{
				if(velx > 0)
				{
					velx -= friction;
					if(velx < 0)
						velx = 0;
				}
				else if(velx < 0)
				{
					velx += friction;
					if(velx > 0)
						velx = 0;
				}
				if(vely > 0)
				{
					vely -= friction;
					if(vely < 0)
						vely = 0;
				}
				else if(vely < 0)
				{
					vely += friction;
					if(vely > 0)
						vely = 0;
				}
			}
			setcolor(2);
			if(x < 571)
			{
				x = 571;
				velx = velx * (-1);
				velx /= 2;
			}
			else if(x > 929)
			{
				x = 929;
				velx = velx * (-1);
				velx /= 2;
			}
			if(y < 51 && (x > 780 || x < 720))
			{
				y = 51;
				vely = vely * (-1);
				vely /= 2;
			}
			else if(y > 749 && (x > 770 || x < 730))
			{
				y = 749;
				vely = vely * (-1);
				vely /= 2;
			}
			circle(x, y, r);
			setfillstyle(SOLID_FILL, 2);
			floodfill(x, y, 2);
		}
};
Ball ball;
class User
{
	public:
		int x, y;
		void Reset(int X, int Y)
		{
			x = X;
			y = Y;
		}
		void Draww()
		{
			int tempx = x, tempy = y;
			x += pos.x - prev.x;
			y += pos.y - prev.y;
			float dis = sqrt((x - ball.x)*(x - ball.x) + (y - ball.y)*(y - ball.y));
			if(dis < 60)
			{
				x = tempx;
				y = tempy;
				velx = velx * (-1);
				vely = vely * (-1);
				velx += (pos.x - prev.x);
				vely += (pos.y - prev.y);
			}
			if(x > 920)
				x = 920;
			else if(x < 580)
				x = 580;
			if(y > 740)
				y = 740;
			else if(y < 430)
				y = 430;
			setcolor(9);
			circle(x, y, 30);
			setfillstyle(SOLID_FILL, 9);
			floodfill(x, y, 9);
			setcolor(1);
			circle(x, y, 10);
			setfillstyle(SOLID_FILL, 1);
			floodfill(x, y, 1);
		}
};
User user;
class CPU
{
	public:
		float x, y;
		void Reset(int X, int Y)
		{
			x = X;
			y = Y;
		}
		void Draww()
		{
			float tempx = x, tempy = y;
			if(ball.y < 400)
			{
				x += (ball.x - x)/factor;
				if(y < ball.y)
					y += 5;
				else
					y -= 5;
			}
			else
				y = max(100, int(y - 10));
			float dis = sqrt((x - ball.x)*(x - ball.x) + (y - ball.y)*(y - ball.y));
			if(dis < 60)
			{
				velx = velx * (-1);
				vely = vely * (-1);
				velx += (x - tempx)/2;
				vely += (y - tempy)/2;
				velx += (rand() % 101) - 50;
				vely += (rand() % 101) - 30;
				x = tempx;
				y = tempy;
			}
			if(x > 920)
				x = 920;
			else if(x < 580)
				x = 580;
			if(y > 370)
				y = 370;
			else if(y < 60)
				y = 60;
			setcolor(12);
			circle(x, y, 30);
			setfillstyle(SOLID_FILL, 12);
			floodfill(x, y, 12);
			setcolor(4);
			circle(x, y, 10);
			setfillstyle(SOLID_FILL, 4);
			floodfill(x, y, 4);
		}
};
CPU cpu;

main()
{
	initwindow(1920, 1080, "Game", -3, -3, true, true);
	int page = 0;
	while(1)
	{
	int userscore = 0, cpuscore = 0, Y;
	char users[20], cpus[20];
	Y = 800;
	setactivepage(page);
	setvisualpage(page);
	settextstyle(0, 0, 10);
	setcolor(WHITE);
	cleardevice();
	outtextxy(430, 100, "Air Hockey");
	settextstyle(0, 0, 4);
	outtextxy(530, 300, "Choose Difficulty : ");
	while(Y > 400)
	{
		outtextxy(200, Y, "Easy");
		outtextxy(700, Y, "Medium");
		outtextxy(1200, Y, "Hard");
		Y--;
	}
	while(1)
	{
		GetCursorPos(&pos);
		if(pos.x > 1100 && GetAsyncKeyState(VK_LBUTTON))
		{
			factor = 10;
			break;
		}
		else if(pos.x > 600 && GetAsyncKeyState(VK_LBUTTON))
		{
			factor = 20;
			break;
		}
		else if(GetAsyncKeyState(VK_LBUTTON))
		{
			factor = 30;
			break;
		}
	}
	beginning:
	userscore = 0, cpuscore = 0;
	ball.Reset(750, 600);
	start:
	user.Reset(750, 700);
	cpu.Reset(750, 100);
	velx = 0, vely = 0;
	SetCursorPos(user.x, user.y);
	GetCursorPos(&pos);
	while(game)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		test = (test + 1) % 10;
	
		//Score
		setcolor(BLUE);
		sprintf(users, "%d", userscore);
		sprintf(cpus, "%d", cpuscore);
		outtextxy(2, 10, "You");
		outtextxy(2, 40, users);
		outtextxy(1400, 10, "CPU");
		outtextxy(1400, 40, cpus);
		outtextxy(1150, 700, "Created By:");
		outtextxy(1150, 730, "Atul Raj");
		outtextxy(1150, 760, "21JE0195");
		outtextxy(1150, 790, "IIT (ISM)");
		
		//Platform
		setfillstyle(SOLID_FILL, 7);
		floodfill(1, 100, BLUE);
		setcolor(0);
		rectangle(550, 30, 950, 770);  // 550, 950, 30, 770
		line(550, 400, 950, 400);
		circle(750, 400, 20);
		arc(750, 30, 180, 360, 30);
		arc(750, 770, 0, 180, 30);
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(750, 40, BLACK);
		floodfill(750, 760, BLACK);
	
		//User
		prev = pos;
		GetCursorPos(&pos);
		user.Draww();
		if(pos.x < 50 || pos.x > 1450)
		{
			SetCursorPos(user.x, pos.y);
			pos.x = user.x;
		}
		if(pos.y < 30 || pos.y > 780)
		{
			SetCursorPos(pos.x, user.y);
			pos.y = user.y;
		}
		
		//CPU
		cpu.Draww();
	
		//Ball
		ball.Draww();
		
		//Score
		if(ball.y < 51)
		{
			if(++userscore == 7)
			{
				cleardevice();
				outtextxy(650, 400, "You Win");
				setvisualpage(page);
				delay(3000);
				goto beginning;
			}
			else
				outtextxy(650, 400, "Goal!!!");
			ball.Reset(750, 600);
			setvisualpage(page);
			delay(3000);
			goto start;
		}
		else if(ball.y > 749)
		{
			if(++cpuscore == 7)
			{
				cleardevice();
				outtextxy(650, 400, "You Lose");
				setvisualpage(page);
				delay(3000);
				goto beginning;
			}
			ball.Reset(750, 200);
			outtextxy(700, 400, "Oh!!!");
			setvisualpage(page);
			delay(3000);
			goto start;
		}
		page = 1 - page;
	}
	}
}
