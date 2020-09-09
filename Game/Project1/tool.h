#pragma once

class Tools
{
public:
	Tools* next;
	float x0;
	float y0;
	float x;
	float y;
	float r;//判定半径
	double theta;//参数方程的角
	long t;
	long t0;
	virtual void Init(float, float, double) = 0;
	virtual void Draw() = 0;
	virtual void Move()=0 ;
	virtual void Check()=0;
	virtual void Function() = 0;
};

class Tool1 :public Tools//加分
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool2:public Tools//加分
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool3:public Tools//加分
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool4:public Tools//加分
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool5:public Tools//加火力
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool6 :public Tools//加bomb
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool7 :public Tools//加生命
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};
