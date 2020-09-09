#pragma once
extern enum State;

class PlayerBullet	//�Ի��ӵ�
{
public:
	PlayerBullet* next;
	State state;
	float x0;
	float y0;
	float x;
	float y;
	double theta;
	float t0;
	float t;
	int damage;

	long t1;
	int fhit;
	IMAGE* frame;
	int hitframe;

	virtual void BulletInit(float,float,double)=0;	//�ӵ���ʼλ��
	virtual void Move()=0;
	//virtual void Damage()=0;
	virtual void Check()=0;
	virtual void Draw()=0;
	virtual void Drawhiting() = 0;
};

class PlayerBulletA: public PlayerBullet	//�Ի��ӵ�
{
public:
	//PlayerBulletA* next;
	void BulletInit(float, float, double);	//�ӵ���ʼλ��
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};

class PlayerBulletB : public PlayerBullet	//�Ի��ӵ�
{
public:
	//PlayerBulletB* next;
	void BulletInit(float, float, double);	//�ӵ���ʼλ��
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};

class PlayerBulletC : public PlayerBullet	//�Ի��ӵ�
{
public:
	//PlayerBulletC* next;
	void BulletInit(float, float, double);	//�ӵ���ʼλ��
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};


class Players	//�Ի�A
{
public:
	State state;
	float x;
	float y;
	float r;
	float v;
	float vmax;
	float vmin;
	int bombdamage;
	float bombr;

	PlayerBullet* head;
	PlayerBullet* end;
	long tshoot;	//��������
	long t1; //��һ�����ʱ��
	long tbomb0;	//��һ�η�bombʱ��
	long tbomb;		//bomb�ͷż��
	long tdead;		//����ʱ��
	long tcantbeharmed0;	//�޵п�ʼʱ��
	long tcantbeharmed;	//�޵�ʱ��

	long t0;	//��һ֡��ʾ��ʱ��
	int framenumber;	//֡��
	int movingframe0;	//�ƶ���ʼ֡
	int movingframe1;	//�ƶ�����֡
	int dyingframe0;	//������ʼ֡
	int dyingframe1;	//��������֡
	int bombframe0;		//bomb��ʼ֡
	int bombframe1;		//bomb����֡
	int movingframe;
	int dyingframe;
	int bombframe;
	int f;	//��ǰ֡
	int fbomb;	//bomb��ǰ֡
	//IMAGE frame[100];	//֡ͼ��
	IMAGE* frame[3];

	virtual void Init()=0;	//��ʼ���Ի�
	virtual void Move()=0;	//��ҿ����Ի��ƶ�
	virtual void Draw(long)=0;
	virtual void Shoot()=0;	//�Ի����
	virtual void Bomb() = 0;	//�Ի��ͷ�bomb
};

class PlayerA: public Players	//�Ի�A
{
public:
	void Init();	//��ʼ���Ի�
	void Move();	//��ҿ����Ի��ƶ�
	void Draw(long);
	void Shoot();	//�Ի����
	void Bomb();	//�Ի��ͷ�bomb
};

class PlayerB : public Players	//�Ի�B
{
public:
	void Init();	//��ʼ���Ի�
	void Move();	//��ҿ����Ի��ƶ�
	void Draw(long);
	void Shoot();	//�Ի����
	void Bomb();	//�Ի��ͷ�bomb
};

class PlayerC : public Players	//�Ի�C
{
public:
	void Init();	//��ʼ���Ի�
	void Move();	//��ҿ����Ի��ƶ�
	void Draw(long);
	void Shoot();	//�Ի����
	void Bomb();	//�Ի��ͷ�bomb
};


long int Calculatescore(long);	//�Ʒֺ���
