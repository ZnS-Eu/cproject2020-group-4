#pragma once

class Tools
{
public:
	Tools* next;
	float x0;
	float y0;
	float x;
	float y;
	float r;//�ж��뾶
	double theta;//�������̵Ľ�
	long t;
	long t0;
	virtual void Init(float, float, double) = 0;
	virtual void Draw() = 0;
	virtual void Move()=0 ;
	virtual void Check()=0;
	virtual void Function() = 0;
};

class Tool1 :public Tools//�ӷ�
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool2:public Tools//�ӷ�
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool3:public Tools//�ӷ�
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool4:public Tools//�ӷ�
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool5:public Tools//�ӻ���
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool6 :public Tools//��bomb
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};

class Tool7 :public Tools//������
{
public:
	void Init(float, float, double);
	void Move();
	void Draw();
	void Check();
	void Function();
};
