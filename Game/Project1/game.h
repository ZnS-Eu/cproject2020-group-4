#pragma once
#include "player.h"
enum State{alive, dying, dead, title, playerselect, game,
		   pause, loading, end, stageclear, win, lost , cantbeharmed, bomb} ;

class Games
{
public:
	State state;
	float fps;
	long score;
	int life;
	int nplayer;
	int power;
	int bomb;
	int stagenumber;
	wchar_t Name[100];
	long t0;	//游戏开始时间
	long t;		//游戏当前时间
	long tpause;	//总共暂停时间
	struct dat
	{
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
	};
	struct tmp
	{
		//wchar_t name[100];
		char name[100];
		dat date;
		int score;
		int life;
	};
	time_t now;
	tm *date;
	struct tmp play[100];

	void GameInit();
	void Title();
	void PlayerSelect();
	void Game();
	int Pause();	//传递当前时间
	void PlayerData();
	void Showdata();
	void Ending();
	void Writedata();
	void Readdata();
};
