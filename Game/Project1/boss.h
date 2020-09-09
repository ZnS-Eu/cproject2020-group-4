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
	float r;//�ж��뾶
	double theta;//�������̵Ľ�
	double bullettheta;
	int strength;
	long lifetime;
	long t0;//����ʱ��
	long t;//����ʱ��

	long t1;	//��һ�η���ʱ��

	long t2;	//��һ֡��ʾ��ʱ��
	int framenumber;	//֡��
	int f;	//��ǰ֡
	//IMAGE frame[100];	//֡ͼ��
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
	long tim[8];	//ÿһ���ӵ�����ʱ��

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
	long tim[1000];	//ÿһ���ӵ�����ʱ��

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
	long tim[500];	//ÿһ���ӵ�����ʱ��

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
	long tim[500];	//ÿһ���ӵ�����ʱ��

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
	long tim[500];	//ÿһ���ӵ�����ʱ��

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
	long tim[2000];	//ÿһ���ӵ�����ʱ��

	void Init(float, float, double);
	void Shoot(Boss*);
	void Move();
	void Draw();
	//void Check(Boss*);
	void Drawdying(long);
	void score();
};