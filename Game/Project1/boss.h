#pragma once
#include <easyx.h>
#include <conio.h>
#include "bossbullet.h"
//enum State { alive, dying, dead };
extern enum State;

class Boss
{
public:
	Boss* next;
	State state;
	BossBullets* headbullet;
	BossBullets* endbullet;
	bool final;
	float x0;
	float y0;
	float x;
	float y;
	float r;//判定半径
	double theta;//参数方程的角
	double bullettheta;
	int strength;
	long lifetime;
	long t0;//产生时间
	long t;//存在时长

	long t1;	//上一次发射时间

	long t2;	//上一帧显示的时间
	int framenumber;	//帧数
	int f;	//当前帧
	//IMAGE frame[100];	//帧图像
	IMAGE* frame;

	long t3;
	int fmove;
	IMAGE* framemove;
	int moveframe;

	virtual void Init(float, float, double) = 0;
	virtual void Shoot(Boss*) = 0;
	virtual void Move() = 0;
	virtual void Draw() = 0;
	virtual void Drawdying(long) = 0;
	virtual void score() = 0;
	void Check(Boss*);
};

class BossA : public Boss
{
public:
	long tim[8];	//每一颗子弹发射时间

	void Init(float,float,double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};

class BossB : public Boss
{
public:
	long tim[1000];	//每一颗子弹发射时间

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};

class BossC : public Boss
{
public:
	long tim[500];	//每一颗子弹发射时间

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};

class BossD : public Boss
{
public:
	long tim[500];	//每一颗子弹发射时间

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};

class BossE : public Boss
{
public:
	long tim[500];	//每一颗子弹发射时间

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};

class BossF : public Boss
{
public:
	int group;
	long tim[2000];	//每一颗子弹发射时间

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};