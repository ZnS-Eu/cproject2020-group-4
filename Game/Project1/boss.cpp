#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "game.h"
#include "loadresource.h"
#include "player.h"
#include "stage.h"
#include "boss.h"
#define  PI 3.14159265

IMAGE A;

extern IMAGE img[500];
extern Games Game1;
extern Stage* stage;
extern Players* Player;

/*boss通用判定*/

void Boss::Check(Boss* p)
{
	float d12, d1;
	float d22, d2;
	PlayerBullet* a;
	PlayerBullet* ittt;
	a = Player->head;
	ittt = Player->head;
	while (a != NULL && a->next != NULL)
	{
		/*检测自机子弹与敌机的碰撞*/
		d12 = (a->next->x - this->x) * (a->next->x - this->x) + (a->next->y - this->y) * (a->next->y - this->y);
		d1 = sqrt(d12);
		if (d1 <= this->r)
		{
			if (a->next->state == alive)
			{
				this->strength = this->strength - a->next->damage;
				a->next->state = dying;
			}
		}
		if (a != Player->head && a != Player->head->next && a->next->state == dead)
		{
			ittt = a->next->next;
			if (a->next == Player->end)
				Player->end = a;
			delete(a->next);
			a->next = ittt;
		}
		a = a->next;
	}
	
	/*检测自机与敌机的碰撞*/
	d22 = (Player->x - this->x) * (Player->x - this->x) + (Player->y - this->y) * (Player->y - this->y);
	d2 = sqrt(d22);
	if (d2 < (Player->r + this->r) && Player->state != dying&&Player->state!=bomb
		&& Game1.t - Player->tdead >= Player->tcantbeharmed)
	{
		Game1.life--;
		Game1.bomb = 3;
		Player->state = dying;
		Player->f = Player->dyingframe0;
	}
	/*检测bomb伤害*/
	if (Player->state == bomb&&d2<=Player->bombr)
	{
		this->strength = this->strength - Player->bombdamage;
	}
	Boss* itt;
	Boss* q;
	if (this->next != NULL)
	{
		if (( this->next->strength <= 0
			|| this->next->t >= this->next->lifetime) 
			&& this->next->state == alive)
		{
			this->next->state = dying;
			if(this->next->strength<=0)
				this->score();
		}
		if (this->next->state == dead)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endboss)
				{
					stage->endboss = this;
				}
				if (this->next->final == true)
					//stage->clear = true;
					stage->tclear = Game1.t;
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endboss)
				{
					stage->endboss = this;
				}
				if (this->next->final == true)
					//stage->clear = true;
					stage->tclear = Game1.t;
				delete(this->next);
				this->next = NULL;
			}
		}
		/*if (this->next->next == NULL
			&& (this->next->strength <= 0)
			&& this->next->state == alive)
		{
			this->next->state = dying;
		}
		if (this->next->next == NULL && this->next->state == dead)
		{
			
		}*/
	}
}

/******************************************************/
/********************BossA(道中杂鱼)********************/
/******************************************************/

void BossA::Init(float x, float y, double theta)
{
	state = alive;
	final = false;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->theta = theta;
	this->strength = 30;
	this->lifetime = 10000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	for (j = 0; j < 3; j++)
	{
		tim[j] = this->t0 +500+ 500 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 10;
	f = 0;
	frame = &img[20];

	t3 = 0;
	moveframe = 12;
	fmove = 0;
	framemove = &img[97];
}

void BossA::Shoot(Boss*)
{
	if (this->state != dying)
	{
		int i;
		for (i = 0; i < 3; i++)
		{
			if (Game1.t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				BossBullets* a = new BossBulletD;
				stage->endbullet->next = a;
				stage->endbullet->next->BulletInit(this->x, this->y, PI - atan((Player->x - this->x) / (Player->y - this->y)));
				stage->endbullet = a;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 3; i++)
			tim[i] = 0;
	}
}

void BossA::Move()
{
	x = x0+cos(theta)*0.2*t;
	y = y0-50*sin(0.01*t) ;
	//y = y0 + 0.0002 * t * t;
}

void BossA::Draw()
{
	int v = 100;
	if (state == alive)
	{
		if (t - t3 >= v)
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
			fmove++;
			if (fmove > moveframe-1)
				fmove = 0;
			t3 = t;
		}
		else
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
		}
	}
	//transparentimage(NULL, x, y, &img[4]);
	//putimage(x, y, &img[4]);
}



void BossA::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
	}
}

void BossA::score()
{
	Game1.score = Game1.score + 100;
}

/******************************************************/
/********************BossB(一面关底)********************/
/******************************************************/

void BossB::Init(float x, float y, double theta)
{
	state = alive;
	final = true;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 60;
	this->bullettheta = PI / 6;
	this->strength = 3000;
	this->lifetime = 50000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	for (j = 0; j < 300; j++)
	{
		tim[j] = this->t0 + 2000 + 30 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 29;
	f = 0;
	frame = &img[127];
}

void BossB::Shoot(Boss*)
{
	if (this->state != dying&& this->state != dead)
	{
		int i,j;
		for (i = 0; i < 300; i++)
		{
			if (Game1.t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				for (j = 0; j < 4; j++)
				{
					BossBullets* a = new BossBulletA;
					stage->endbullet->next = a;
					stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta+PI/24*j);
					//stage->endbullet->next->BulletInit(this->x, this->y, 6.28/3 + rand()%100/(float)100*3.14/3*2);
					stage->endbullet = a;
				}
				for (j = 0; j < 4; j++)
				{
					BossBullets* b = new BossBulletA;
					stage->endbullet->next = b;
					stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta + PI / 24 * j+PI);
					//stage->endbullet->next->BulletInit(this->x, this->y, 6.28/3 + rand()%100/(float)100*3.14/3*2);
					stage->endbullet = b;
				}
				this->bullettheta = this->bullettheta + PI / 24*5;
				//this->bullettheta = this->bullettheta + t * t / 10000000;
				//this->bullettheta = rand() * PI;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 300; i++)
			tim[i] = 0;
	}
}

void BossB::Move()
{
	x = x0;
	if (t <= 1000)
	{
		y = y0 + 0.1*t;
	}
	//y = y0 + 0.0002 * t * t;
}

void BossB::Draw()
{
	transparentimage(NULL, x-125, y-143, &img[124]);
	//putimage(x, y, &img[4]);
}



void BossB::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
	}
}

void BossB::score()
{
	Game1.score = Game1.score + 4000;
}

/******************************************************/
/********************BossC(二面道中)********************/
/******************************************************/

void BossC::Init(float x, float y, double theta)
{
	state = alive;
	final = false;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->bullettheta = 0;
	this->strength = 30;
	this->lifetime = 8000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	for (j = 0; j < 6; j++)
	{
		tim[j] = this->t0 + 1000 + 250 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 10;
	f = 0;
	frame = &img[20];

	t3 = 0;
	moveframe = 8;
	fmove = 0;
	framemove = &img[88];
}

void BossC::Shoot(Boss*)
{
	if (this->state != dying)
	{
		int i, j;
		for (i = 0; i < 8; i++)
		{
			if (Game1.t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				for (j = 0; j < 8; j++)
				{
					BossBullets* a = new BossBulletD;
					stage->endbullet->next = a;
					stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta + PI / 4 * j+PI/8);
					//stage->endbullet->next->BulletInit(this->x, this->y, 6.28/3 + rand()%100/(float)100*3.14/3*2);
					stage->endbullet = a;
				}
				//this->bullettheta = this->bullettheta + PI / 24 * 5;
				//this->bullettheta = this->bullettheta + t * t / 10000000;
				//this->bullettheta = rand() * PI;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 300; i++)
			tim[i] = 0;
	}
}

void BossC::Move()
{
	x = x0;
	y = y0 + 0.1 * t*t/1000;
	//y = y0 + 0.0002 * t * t;
}

void BossC::Draw()
{
	int v = 100;
	if (state == alive)
	{
		if (t - t3 >= v)
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
			fmove++;
			if (fmove > moveframe - 1)
				fmove = 0;
			t3 = t;
		}
		else
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
		}
	}
	//putimage(x, y, &img[4]);
}



void BossC::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
	}
}

void BossC::score()
{
	Game1.score = Game1.score + 200;
}

/******************************************************/
/********************BossD(二面关底)********************/
/******************************************************/

void BossD::Init(float x, float y, double theta)
{
	state = alive;
	final = true;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 100;
	this->bullettheta = PI / 6;
	this->strength = 10000;
	this->lifetime = 100000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	for (j = 0; j < 300; j++)
	{
		tim[j] = this->t0 + 2000 + 200 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 29;
	f = 0;
	frame = &img[127];

	t3 = 0;
	moveframe = 15;
	fmove = 0;
	framemove = &img[109];
}

void BossD::Shoot(Boss*)
{
	if (this->state != dying)
	{
		int i, j;
		for (i = 0; i < 300; i++)
		{
			if (Game1.t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				for (j = 0; j < 8; j++)
				{
					BossBullets* a = new BossBulletA;
					stage->endbullet->next = a;
					//stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta + PI / 24 * j);
					stage->endbullet->next->BulletInit(this->x, this->y, 6.28/3 + rand()%100/(float)100*3.14/3*2);
					stage->endbullet = a;
				}
				//this->bullettheta = this->bullettheta + PI / 24 * 5;
				//this->bullettheta = this->bullettheta + t * t / 10000000;
				//this->bullettheta = rand() * PI;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 300; i++)
			tim[i] = 0;
	}
}

void BossD::Move()
{
	x = x0;
	if (t <= 1000)
	{
		y = y0 + 0.1 * t;
	}
	//y = y0 + 0.0002 * t * t;
}

void BossD::Draw()
{
	int v = 50;
	if (state == alive)
	{
		if (t - t3 >= v)
		{
			transparentimage(NULL, x - 150, y - 153, &framemove[fmove]);
			fmove++;
			if (fmove > moveframe - 1)
				fmove = 0;
			t3 = t;
		}
		else
		{
			transparentimage(NULL, x - 150, y - 153, &framemove[fmove]);
		}
	}
	//putimage(x, y, &img[4]);
}



void BossD::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
	}
}

void BossD::score()
{
	Game1.score = Game1.score + 4000;
}


/******************************************************/
/********************BossE(三面道中)********************/
/******************************************************/

void BossE::Init(float x, float y, double theta)
{
	state = alive;
	final = false;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->bullettheta = 0;
	this->strength = 600;
	this->lifetime = 20000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	for (j = 0; j < 48; j++)
	{
		tim[j] = 2000 + 400 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 10;
	f = 0;
	frame = &img[20];

	t3 = 0;
	moveframe = 12;
	fmove = 0;
	framemove = &img[97];
}

void BossE::Shoot(Boss*)
{
	if (this->state != dying)
	{
		int i, j;
		for (i = 0; i < 48; i++)
		{
			if (this->t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				for (j = 0; j < 24; j++)
				{
					BossBullets* a = new BossBulletB;
					stage->endbullet->next = a;
					stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta + PI / 12 * j);
					//stage->endbullet->next->BulletInit(this->x, this->y, 6.28/3 + rand()%100/(float)100*3.14/3*2);
					stage->endbullet = a;
				}
				this->bullettheta = this->bullettheta + PI / 48 ;
				//this->bullettheta = this->bullettheta + t * t / 10000000;
				//this->bullettheta = rand() * PI;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 300; i++)
			tim[i] = 0;
	}
}

void BossE::Move()
{
	x = x0;
	if (t <= 2000)
	{
		y = y0 + 0.05 * t;
	}
	//y = y0 + 0.0002 * t * t;
}

void BossE::Draw()
{
	int v = 100;
	if (state == alive)
	{
		if (t - t3 >= v)
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
			fmove++;
			if (fmove > moveframe - 1)
				fmove = 0;
			t3 = t;
		}
		else
		{
			transparentimage(NULL, x - 40, y - 37, &framemove[fmove]);
		}
	}
	//transparentimage(NULL, x, y, &img[4]);
	//putimage(x, y, &img[4]);
}



void BossE::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 74, y - 79, &this->frame[this->f]);
	}
}

void BossE::score()
{
	Game1.score = Game1.score + 200;
}

/******************************************************/
/********************BossF(三面关底)********************/
/******************************************************/

void BossF::Init(float x, float y, double theta)
{
	state = alive;
	final = true;
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 200;
	this->bullettheta = PI / 6;
	this->strength = 9000;
	this->lifetime = 100000;
	this->t0 = Game1.t;
	this->t = 0;

	/*与发射子弹相关的部分*/
	int j;
	group = 0;
	for (j = 0; j < 1500; j++)
	{
		tim[j] = this->t0 + 2000 + 40 * j;
	}

	/*动画部分*/
	t2 = 0;
	framenumber = 29;
	f = 0;
	frame = &img[127];

}

void BossF::Shoot(Boss*)
{
	if (this->state != dying)
	{
		int i, j;
		for (i = 0; i < 1500; i++)
		{
			if (Game1.t >= tim[i] && tim[i] != 0)
			{
				tim[i] = 0;
				for (j = 0; j < 5; j++)
				{
					BossBullets* a = new BossBulletC;
					stage->endbullet->next = a;
					stage->endbullet->next->BulletInit(this->x, this->y, this->bullettheta + 2*PI /5 * j);
					//stage->endbullet->next->BulletInit(this->x, this->y, 6.28 / 3 + rand() % 100 / (float)100 * 3.14 / 3 * 2);
					stage->endbullet = a;
				}
				//this->bullettheta = this->bullettheta + PI / 24 * 5;
				//this->bullettheta = this->bullettheta + t * t / 5400000;
				//this->bullettheta = this->bullettheta + t * t / 9500000;
				//this->bullettheta = this->bullettheta + t/4500;
				this->bullettheta = this->bullettheta + PI / 384 * group;
				group++;;
				//this->bullettheta = rand() * PI;
			}
		}
	}
	if (this->state == dying)
	{
		int i;
		for (i = 0; i < 300; i++)
			tim[i] = 0;
	}
}

void BossF::Move()
{
	x = x0;
	if (t <= 1000)
	{
		y = y0 + 0.1 * t;
	}
	//y = y0 + 0.0002 * t * t;
}

void BossF::Draw()
{
	transparentimage(NULL, x - 150, y - 256, &img[125]);
	//putimage(x, y, &img[4]);
}



void BossF::Drawdying(long t)
{
	int v = 60;
	if (t - this->t0 >= v)
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
		this->f++;
		if (this->f > this->framenumber - 1)
			this->state = dead;
		this->t0 = Game1.t;
	}
	else
	{
		transparentimage(NULL, x - 125, y - 101, &this->frame[this->f]);
	}
}

void BossF::score()
{
	Game1.score = Game1.score + 4000;
}