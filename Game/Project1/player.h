#pragma once
extern enum State;

class PlayerBullet	//自机子弹
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

	virtual void BulletInit(float,float,double)=0;	//子弹初始位置
	virtual void Move()=0;
	//virtual void Damage()=0;
	virtual void Check()=0;
	virtual void Draw()=0;
	virtual void Drawhiting() = 0;
};

class PlayerBulletA: public PlayerBullet	//自机子弹
{
public:
	//PlayerBulletA* next;
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};

class PlayerBulletB : public PlayerBullet	//自机子弹
{
public:
	//PlayerBulletB* next;
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};

class PlayerBulletC : public PlayerBullet	//自机子弹
{
public:
	//PlayerBulletC* next;
	void BulletInit(float, float, double);	//子弹初始位置
	void Move();
	void Damage();
	void Check();
	void Draw();
	virtual void Drawhiting();
};


class Players	//自机A
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
	long tshoot;	//攻击速率
	long t1; //上一次射击时间
	long tbomb0;	//上一次放bomb时间
	long tbomb;		//bomb释放间隔
	long tdead;		//死亡时间
	long tcantbeharmed0;	//无敌开始时间
	long tcantbeharmed;	//无敌时间

	long t0;	//上一帧显示的时间
	int framenumber;	//帧数
	int movingframe0;	//移动开始帧
	int movingframe1;	//移动结束帧
	int dyingframe0;	//死亡开始帧
	int dyingframe1;	//死亡结束帧
	int bombframe0;		//bomb开始帧
	int bombframe1;		//bomb结束帧
	int movingframe;
	int dyingframe;
	int bombframe;
	int f;	//当前帧
	int fbomb;	//bomb当前帧
	//IMAGE frame[100];	//帧图像
	IMAGE* frame[3];

	virtual void Init()=0;	//初始化自机
	virtual void Move()=0;	//玩家控制自机移动
	virtual void Draw(long)=0;
	virtual void Shoot()=0;	//自机射击
	virtual void Bomb() = 0;	//自机释放bomb
};

class PlayerA: public Players	//自机A
{
public:
	void Init();	//初始化自机
	void Move();	//玩家控制自机移动
	void Draw(long);
	void Shoot();	//自机射击
	void Bomb();	//自机释放bomb
};

class PlayerB : public Players	//自机B
{
public:
	void Init();	//初始化自机
	void Move();	//玩家控制自机移动
	void Draw(long);
	void Shoot();	//自机射击
	void Bomb();	//自机释放bomb
};

class PlayerC : public Players	//自机C
{
public:
	void Init();	//初始化自机
	void Move();	//玩家控制自机移动
	void Draw(long);
	void Shoot();	//自机射击
	void Bomb();	//自机释放bomb
};


long int Calculatescore(long);	//计分函数
