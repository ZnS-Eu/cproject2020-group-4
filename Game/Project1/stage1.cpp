#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "loadresource.h"
#include "player.h"
#include "stage.h"
#include "boss.h"
#include "bossbullet.h"
#include "tool.h"
#define  PI 3.14159265


extern IMAGE img[500];
extern Games Game1;
extern Players* Player;
extern Stage* stage;

//Stage1 stage[3];

void Stage1::Createstage()
{
	clear = false;
	
	int i;
	long n;

	x = 350;
	y = 0;

	tclear = 0;
	for (i = 0; i < 19; i++)
	{
		tim[i] = 5000 + 1000 * i;
	}
	for (i = 0; i < 19; i++)
	{
		tim[i + 19] = 5500 + 1000 * i;
	}
	tim[39] = 30000;
	headboss = new BossA;
	endboss = headboss;
	headboss->Init(0, 0, 0);
	headbullet = new BossBulletA;
	endbullet = headbullet;
	headtool = new Tool1;
	endtool= headtool;
	//headboss->Init(-50, -50, 0);
	for (n = 0; n < 70; n++)
	{
		tim2[n] = 1000+2000*n;
	}
}

void Stage1::Clearstage()
{
	int i;
	for (i = 0; i < 20; i++)
	{
		tim[i] =0;
	}
	/*Boss* a;
	Boss* b;
	a = headboss;
	while (a != NULL)
	{
		b = a;
		a = a->next;
		delete (b);
	}*/

	/*清除自机子弹*/
	headtool = NULL;
	endtool = NULL;
	PlayerBullet* p1;
	PlayerBullet* q1;
	p1 = Player->head;
	q1 = p1;
	while (p1 != NULL)
	{
		q1 = p1;
		p1 = p1->next;
		delete(q1);
	}
	Player->head = NULL;
	/*清除boss*/
	Boss* p2;
	Boss* q2;
	p2 = headboss;
	q2 = p2;
	while (p2 != NULL)
	{
		q2 = p2;
		p2 = p2->next;
		delete(q2);
	}
	headboss = NULL;
	/*清除boss子弹*/
	BossBullets* p3;
	BossBullets* q3;
	p3 = headbullet;
	q3 = p3;
	while (p3 != NULL)
	{
		q3 = p3;
		p3 = p3->next;
		delete(q3);
	}
	headbullet = NULL;
	headtool = NULL;
	/*清除道具*/
	Tools* p4;
	Tools* q4;
	p4 = headtool;
	q4 = p4;
	while(p4!=NULL)
	{
		q4 = p4;
		p4 = p4->next;
		delete(q4);
	}
	/*清除关卡*/
	delete(stage);
	stage = NULL;

	/*清除自机*/
	//delete(Player);
}

void Stage1::Createboss()
{
	int i;
	for (i = 0; i < 19; i++)
	{
		if (Game1.t >= tim[i]&& tim[i]!=0)
		{
			tim[i] = 0;
			Boss* a = new BossA;
			endboss->next = a;
			endboss->next->Init(380, 150, 0);
			endboss = a;
			a = NULL;
			Boss* b = new BossA;
			endboss->next = b;
			endboss->next->Init(900, 150, PI);
			endboss = b;

		}
	}
	if (Game1.t >= tim[39] && tim[39] != 0)
	{
		tim[39] = 0;
		Boss* a = new BossB;
		endboss->next = a;
		endboss->next->Init(680, 15, 0);
		endboss = a;
	}
	Boss* it=headboss;
	while(it!=NULL)
	{
		it->Check(it);
		if (it != headboss)
		{
			it->t = (Game1.t - it->t0);   //以毫秒为单位计时
			if (it->state == alive)
			{
				it->Move();
				it->Draw();
			}
			if (it->state == dying)
			{
				it->Drawdying(Game1.t);
			}
			it->Shoot(it);
		}
		it = it->next;
	}

	BossBullets* itt = headbullet;
	while (itt != NULL)
	{
		itt->t = (Game1.t - itt->t0);   //以毫秒为单位计时
		itt->Move();
		itt->Draw();
		itt->BulletCheck();
		itt = itt->next;
	}

	if (Game1.t - stage->tclear > 3000 && stage->tclear != 0)
		stage->clear = true;
}

void Stage1::Creattool()
{
	//srand(Game1.t);
	int n;
	for (n = 0; n < 3; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool1;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 3;n < 4; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool5;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 4;n < 7;n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool2;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 7; n < 10;n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool3;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n=10;n<11;n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0&&Game1.power<4)
		{
			tim2[n] = 0;
			Tools* a = new Tool6;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 11; n <12 ; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0 && Game1.power < 4)
		{
			tim2[n] = 0;
			Tools* a = new Tool7;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 12; n <=70; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0 && Game1.power < 4)
		{
			tim2[n] = 0;
			Tools* a = new Tool4;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	Tools* it = headtool;
	while (it != NULL)
	{
		it->t = (Game1.t - it->t0);   //以毫秒为单位计时
		it->Move();
		it->Draw();
		it->Check();
		it = it->next;
	}
}



void Stage1::Draw()
{
	putimage(stage->x, stage->y, &img[12]);
	putimage(stage->x, stage->y-767, &img[12]);
	if (stage->y >= 767)
		stage->y = 0;
	stage->y = stage->y + 1;
}


void Stage1::Drawprestage()
{
	long t0 = clock();
	int f = 156;
	BeginBatchDraw();
	while (true)
	{
		if (clock() - t0 >= 200)
		{
			transparentimage(NULL, x, y, &img[f]);
			t0 = clock();
			f++;
		}
		else
		{
			transparentimage(NULL, x, y, &img[f]);
		}
		FlushBatchDraw();
		cleardevice();
		if (f > 169)
			break;
	}
}
