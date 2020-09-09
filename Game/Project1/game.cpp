#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include "loadresource.h"
#include "game.h"
#include "player.h"
#include "stage.h"

extern class Games Game1;
//extern class PlayerA Player;
//extern Stage stage[3];
extern IMAGE img[500];

Players* Player=NULL;
Stage* stage=NULL;

void Games::GameInit()
{
	Game1.fps = 60;
	Game1.state = title;
	Game1.score = 0;
	Game1.life = 4;
	Game1.power = 1;
	Game1.bomb = 3;
	Game1.stagenumber = 1;
	Game1.tpause = 0;
}

void Games::Game()
{
	srand(unsigned(time(0)));
	stage = new Stage1;
	Game1.stagenumber = 1;
	Game1.GameInit();
	long tim0, tim1, tim2, tim3;
	if (nplayer == 1)
		Player = new PlayerA;
	if (nplayer == 2)
		Player = new PlayerB;
	if (nplayer == 3)
		Player = new PlayerC;
	(*Player).Init();
	stage->Createstage();
	stage->Drawprestage();
	Game1.t0 = clock();
	while (true)
	{
		Game1.t = clock() - tpause - Game1.t0;
		tim0 = clock();
		BeginBatchDraw();
		stage->Draw();
		stage->Createboss();
		if (Player->state != dying)
		{
			(*Player).Move();
			(*Player).Shoot();
			(*Player).Bomb();
		}
		(*Player).Draw(clock());
		stage->Creattool();
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			tim2 = clock();
			if (Game1.Pause() == 1)
			{
				stage->Clearstage();
				Game1.state = playerselect;
				break;
			}
			tpause = tpause + clock() - tim2;
		}
		transparentimage(NULL, -1, 0, &img[3]);		//显示背景
		//Game1.score = Calculatescore(score);
		Game1.Showdata();
		FlushBatchDraw();
		cleardevice();
		if (Game1.life < 0)
		{
			Game1.state = lost;
			Ending();
			break;
		}
		tim1 = clock();
		while (tim1 - tim0 <= 5)
		{
			tim1 = clock();  //控制帧率
		}
		Game1.fps = 1000 / (tim1 - tim0);
		/*判断是否过关*/
		if (stage->clear == true && Game1.stagenumber == 1)
		{
			stage->Clearstage();
			stage = new Stage2;
			stage->Createstage();
			stage->Drawprestage();
			Player->Init();
			Game1.stagenumber++;
			Game1.t0 =  clock();
		}
		if (stage->clear == true && Game1.stagenumber == 2)
		{
			stage->Clearstage();
			stage = new Stage3;
			stage->Createstage();
			stage->Drawprestage();
			Player->Init();
			Game1.stagenumber++;
			Game1.t0 = clock();
		}
		if (stage->clear == true && Game1.stagenumber == 3)
		{
			stage->Clearstage();
			stage = NULL;
			Game1.state = win;
			Ending();
			break;
		}
	}

	if(stage!=NULL)
		stage->Clearstage();
}


void Games::Title()
{
	int counter = 0,
		stateup0 = 1, statedown0 = 1,
		stateup1 = 1, statedown1 = 1,
		stateenter0 = 1, stateenter1 = 1,
		stateesc0 = 1, stateesc1 = 1;

	long tim0, tim1;

	while (true)
	{
		tim0 = clock();
		stateup1 = GetKeyState(VK_UP);
		statedown1 = GetKeyState(VK_DOWN);
		stateenter1 = GetKeyState(VK_RETURN);
		if (stateup0 >= 0 && stateup1 < 0)
		{
			counter--;
		}
		stateup0 = stateup1;
		if (statedown0 >= 0 && statedown1 < 0)
		{
			counter++;
		}
		statedown0 = statedown1;
		if (counter > 4)
			counter = 0;
		if (counter < 0)
			counter = 4;
		BeginBatchDraw();
		if (counter == 0)
		{
			transparentimage(NULL,-1, 0, &img[69]);
			if (stateenter0 >= 0 && stateenter1 < 0)
			{
				counter = 0;
				PlayerSelect();
				//Game();
			}
		}
		if (counter == 1)
		{
			transparentimage(NULL, -1, 0, &img[70]);
			if (stateenter0 >= 0 && stateenter1 < 0)
				PlayerData();
		}
		if (counter == 2)
		{
			transparentimage(NULL, -1, 0, &img[71]);
			if (stateenter0 >= 0 && stateenter1 < 0);
		}
		if (counter == 3)
		{
			transparentimage(NULL, -1, 0, &img[72]);
			if (stateenter0 >= 0 && stateenter1 < 0);
		}
		if (counter == 4)
		{
			transparentimage(NULL, -1, 0, &img[73]);
			if (stateenter0 >= 0 && stateenter1 < 0)
				closegraph();
		}
		stateenter0 = stateenter1;
		FlushBatchDraw();
		cleardevice();
		tim1 = clock();
		while (tim1 - tim0 <= 1)
		{
			tim1 = clock();  //控制帧率
		}
		Game1.fps = 1000 / (tim1 - tim0);
	}
}

void Games::PlayerSelect()
{
	Sleep(180);
	int counter = 0,
		stateleft0 = 1, stateright0 = 1,
		stateleft1 = 1, stateright1 = 1,
		stateenter0 = 1, stateenter1 = 1,
		stateesc0 = 1, stateesc1 = 1;

	long tim0, tim1;

	while (true)
	{
		if (stage != NULL)
			stage->Clearstage();
		tim0 = clock();
		stateleft1 = GetKeyState(VK_LEFT);
		stateright1 = GetKeyState(VK_RIGHT);
		stateenter1 = GetKeyState(VK_RETURN);
		if (stateleft0 >= 0 && stateleft1 < 0)
		{
			counter--;
		}
		stateleft0 = stateleft1;
		if (stateright0 >= 0 && stateright1 < 0)
		{
			counter++;
		}
		stateright0 = stateright1;
		if (counter > 2)
			counter = 0;
		if (counter < 0)
			counter = 2;
		BeginBatchDraw();
		if (counter == 0)
		{
			putimage(-1, 0, &img[15]);
			if (stateenter0 >= 0 && stateenter1 < 0)
			{
				nplayer=1;
				Game();
			}
		}
		if (counter == 1)
		{
			putimage(-1, 0, &img[16]);
			nplayer = 2;
			if (stateenter0 >= 0 && stateenter1 < 0)
			{
				nplayer = 2;
				Game();
			}
		}
		if (counter == 2)
		{
			putimage(-1, 0, &img[17]);
			nplayer = 3;
			if (stateenter0 >= 0 && stateenter1 < 0)
			{
				nplayer = 3;
				Game();
			}
		}
		stateenter0 = stateenter1;
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			break;
		}
		FlushBatchDraw();
		cleardevice();
		tim1 = clock();
		while (tim1 - tim0 <= 1)
		{
			tim1 = clock();  //控制帧率
		}
		Game1.fps = 1000 / (tim1 - tim0);
	}
}


void Games::Showdata()
{
	int i;
	TCHAR Score[10];
	TCHAR Fps[10];
	TCHAR Player[3];
	TCHAR Power[3];
	TCHAR Bomb[3];
	_stprintf_s(Player, _T("%d"), Game1.life);
	_stprintf_s(Score, _T("%09d"), Game1.score);
	_stprintf_s(Fps, _T("%.2f"), Game1.fps);
	_stprintf_s(Power, _T("%d"), Game1.power);
	_stprintf_s(Bomb, _T("%d"), Game1.bomb);
	//sprintf_s(Score, "%08d", score);
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 35;						// 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("eufb5"));		// 设置字体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = 700;
	settextstyle(&f);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(1000, 100, _T("Score:"));
	outtextxy(1140, 100, Score);
	outtextxy(1000, 150, _T("Player:"));
	//outtextxy(1170, 150, Player);
	for (i = 0; i < Game1.life; i++)
	{
		transparentimage(NULL, 1180+25*i-15, 150, &img[199]);
	}
	outtextxy(1000, 200, _T("Power:"));
	outtextxy(1170, 200, Power);
	outtextxy(1000, 250, _T("Bomb:"));
	//outtextxy(1170, 250, Bomb);
	for (i = 0; i < Game1.bomb; i++)
	{
		transparentimage(NULL, 1170 + 25 * i-15, 250, &img[200]);
	}
	outtextxy(1050, 650, _T("fps:"));
	outtextxy(1150, 650, Fps);
}

int Games::Pause()
{
	IMAGE Pauseimage;
	getimage(&Pauseimage,0,0,1366,768);
	int counter = 0,
		stateup0 = 1, statedown0 = 1,
		stateup1 = 1, statedown1 = 1,
		stateenter0 = 1, stateenter1 = 1,
		stateesc0 = 1, stateesc1 = 1;
	while (true)
	{
		Game1.state = pause;
		BeginBatchDraw();
		putimage(0, 0, &Pauseimage);
		/*putimage(stage->x, stage->y, &img[12]);
		putimage(stage->x, stage->y-767, &img[12]);
		PlayerBullet* it;
		it = Player->head;
		while (it != NULL)
		{
			it->Draw();
			it = it->next;
		}
		transparentimage(NULL, (*Player).x-40, (*Player).y-40, &(*Player).frame[0][(*Player).f]);*/
		transparentimage(NULL, -1, 0, &img[3]);
		Showdata();
		stateup1 = GetKeyState(VK_UP);
		statedown1 = GetKeyState(VK_DOWN);
		stateenter1 = GetKeyState(VK_RETURN);
		stateesc1 = GetKeyState(VK_ESCAPE);
		if (stateup0 >= 0 && stateup1 < 0)
		{
			counter--;
		}
		stateup0 = stateup1;
		if (statedown0 >= 0 && statedown1 < 0)
		{
			counter++;
		}
		statedown0 = statedown1;
		if (counter > 1)
			counter = 0;
		if (counter < 0)
			counter = 1;
		if (counter == 0)
		{
			transparentimage(NULL, -1, 0, &img[6]);
			if (stateenter0 >= 0 && stateenter1 < 0)
				return 0;
		}

		if (counter == 1)
		{
			transparentimage(NULL, -1, 0, &img[7]);
			if (stateenter0 >= 0 && stateenter1 < 0)
				return 1;
		}
		stateenter0 = stateenter1;
		//counter=pausemenu();
		FlushBatchDraw();
		cleardevice();
		
		//if (stateenter0 >= 0 && stateenter1 < 0)
			
	}
}

void Games::Ending()
{
	Game1.score = Game1.score + 2000 * Game1.bomb + 6000 * Game1.life + 500 * Game1.power;
	if (Game1.life < 0)
	{
		Game1.score = Game1.score * 0.6;
	}
	//InputBox(Name, 10, L"您的昵称");
	Writedata();
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &img[87]);
		TCHAR Score[10];
		TCHAR Player[3];
		TCHAR Power[3];
		TCHAR Bomb[3];
		_stprintf_s(Player, _T("%d"), Game1.life);
		_stprintf_s(Score, _T("%09d"), Game1.score);
		_stprintf_s(Power, _T("%d"), Game1.power);
		_stprintf_s(Bomb, _T("%d"), Game1.bomb);
		//sprintf_s(Score, "%08d", score);
		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfHeight = 35;						// 设置字体高度
		_tcscpy_s(f.lfFaceName, _T("楷体"));		// 设置字体
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = 700;
		settextstyle(&f);
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		outtextxy(400, 250, _T("剩余残机数:"));
		outtextxy(800, 250, Player);
		outtextxy(400, 300, _T("火力:"));
		outtextxy(800, 300, Power);
		outtextxy(400, 350, _T("当前剩余炸弹数:"));
		outtextxy(800, 350, Bomb);
		outtextxy(400, 200, _T("总分数:"));
		outtextxy(800, 200, Score);
		outtextxy(600, 500, _T("按Esc键返回标题页面"));
		FlushBatchDraw();
		cleardevice();
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			break;
		}
	}
}


void Games::PlayerData()
{
	Readdata();
	int i;
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &img[198]);
		TCHAR Score[20][10];
		TCHAR Name[20][100];
		TCHAR Life[20][3];
		TCHAR Bomb[3];
		for (i = 0; i < 20; i++)
		{
			_stprintf_s(Name[i], _T("%d/%d/%d %02d:%02d:%02d"), (play[i].date.year), (play[i].date.month), (play[i].date.day), (play[i].date.hour), (play[i].date.minute), (play[i].date.second));
			_stprintf_s(Score[i], _T("%09d"), play[i].score);
			_stprintf_s(Life[i], _T("%d"), play[i].life);
			//_stprintf_s(Score[i], _T("%d"), play[i].life);
		}
		//_stprintf_s(Player, _T("%d"), Game1.life);
		//_stprintf_s(Score, _T("%09d"), Game1.score);
		//_stprintf_s(Power, _T("%d"), Game1.power);
		_stprintf_s(Bomb, _T("%d"), Game1.bomb);
		//sprintf_s(Score, "%08d", score);
		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfHeight = 35;						// 设置字体高度
		_tcscpy_s(f.lfFaceName, _T("楷体"));		// 设置字体
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = 700;
		settextstyle(&f);
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		outtextxy(110, 100, _T("游戏时间"));
		for (i = 0; i < 20; i++)
		{
			if(play[i].date.year!=0)
			outtextxy(50, 150+30*i, Name[i]);
		}
		outtextxy(550, 100, _T("剩余残机数"));
		for (i = 0; i < 20; i++)
		{
			if (play[i].date.year != 0)
			{
				if (play[i].life >= 0)
				{
					outtextxy(610, 150 + 30 * i, Life[i]);
				}
				else
				{
					outtextxy(580, 150 + 30 * i, _T("未通关"));
				}
			}
		}
		outtextxy(1050, 100, _T("总分数"));
		for (i = 0; i < 20; i++)
		{
			if (play[i].date.year != 0)
			outtextxy(1020, 150 +30 * i, Score[i]);
		}
		FlushBatchDraw();
		if (GetKeyState(VK_ESCAPE) < 0)
			break;
	}
}