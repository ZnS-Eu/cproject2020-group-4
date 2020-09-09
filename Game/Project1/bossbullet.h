#pragma once
#include "boss.h"

extern class Boss;

class BossBullets
{
public:
	BossBullets* next;
	bool alive;
	float x0;
	float y0;
	float x;
	float y;
	float r;
	double theta;
	float t0;
	float t;

	virtual void BulletInit(float, float, double) = 0;	//子弹初始位置
	virtual void Move() = 0;
	//virtual void Damage()=0;
	void BulletCheck();
	virtual void Draw() = 0;
};

class BossBulletA : public BossBullets
{
public:
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	//void Damage();
	//void BulletCheck();
	void Draw();
};

class BossBulletB : public BossBullets
{
public:
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	//void Damage();
	//void BulletCheck();
	void Draw();
};

class BossBulletC : public BossBullets
{
public:
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	//void Damage();
	//void BulletCheck();
	void Draw();
};

class BossBulletD : public BossBullets
{
public:
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	//void Damage();
	//void BulletCheck();
	void Draw();
};