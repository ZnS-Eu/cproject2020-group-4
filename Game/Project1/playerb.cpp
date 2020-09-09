#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "game.h"
#include "boss.h"
#include "stage.h"
#include "loadresource.h"
#include "player.h"

#define PI 3.14159265

extern IMAGE img[500];
extern Games Game1;
extern Players* Player;
extern Stage* stage;

void PlayerB::Init()
{
    state = alive;
    x = 680;
    y = 550;
    r = 0;
    v = 0;
    vmax = 5;
    vmin = 2.5;

    head = new PlayerBulletB;
    end = head;
    bombdamage = 100;
    bombr = 200;
    tshoot = 80;
    tbomb0 = 0;
    tbomb = 3000;
    t1 = 0;
    tdead = 0;
    tcantbeharmed = 2000;

    t0 = 0;
    framenumber = 4;
    f = 0;
    fbomb = 14;
    frame[0] = &img[8];
    frame[1] = &img[20];
    frame[2] = &img[30];
    movingframe = 3;
    dyingframe = 9;
    bombframe = 19;
}

void PlayerB::Move()
{
    if (GetKeyState(VK_SHIFT) >= 0)
    {
        v = vmax;
    }
    if (GetKeyState(VK_SHIFT) < 0)
    {
        v = vmin;
    }
    if (GetKeyState(VK_RIGHT) < 0 && x <= 950)
    {
        x = x + v;
    }
    if (GetKeyState(VK_LEFT) < 0 && x >= 410)
    {
        x = x - v;
    }
    if (GetKeyState(VK_UP) < 0 && y >= 50)
    {
        y = y - v;
    }
    if (GetKeyState(VK_DOWN) < 0 && y <= 695)
    {
        y = y + v;
    }
}


void PlayerB::Draw(long t)
{
    int v = 100;
    /*存活时动画*/
    if (state == alive || state == bomb)
    {
        if (t - (*Player).t0 >= v)
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[0][(*Player).f]);
            (*Player).f++;
            if ((*Player).f > (*Player).movingframe)
                (*Player).f = 0;
            if (state != bomb)
                (*Player).t0 = clock();
        }
        else
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[0][(*Player).f]);
        }
    }
    /*死亡时动画*/
    if (state == dying)
    {
        if (t - (*Player).t0 >= v)
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[1][(*Player).f]);
            (*Player).f++;
            if ((*Player).f > (*Player).dyingframe)
            {
                Player->Init();
                Player->tdead = Game1.t;
                Player->state = cantbeharmed;
            }
            (*Player).t0 = clock();
        }
        else
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[1][(*Player).f]);
        }
    }
    /*死亡后无敌时动画*/
    if (state == cantbeharmed)
    {
        if (t - (*Player).t0 >= v * 2)
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[0][(*Player).f]);
            (*Player).f++;
            if ((*Player).f > (*Player).movingframe)
                (*Player).f = 0;
            (*Player).t0 = clock();
        }
        if (t - (*Player).t0 >= 10 && t - (*Player).t0 < v)
        {
            transparentimage(NULL, x - 40, y - 40, &(*Player).frame[0][(*Player).f]);
        }
        if (Game1.t - tdead >= tcantbeharmed)
            state = alive;
    }

    /*放b时动画*/
    if (state == bomb)
    {
        if (t - (*Player).t0 >= v / 2)
        {
            transparentimage(NULL, x - 200, y - 200, &(*Player).frame[2][(*Player).fbomb]);
            (*Player).fbomb++;
            if ((*Player).fbomb > (*Player).bombframe)
                (*Player).fbomb = 0;
            (*Player).t0 = clock();
        }
        else
        {
            transparentimage(NULL, x - 200, y - 200, &(*Player).frame[2][(*Player).fbomb]);
        }
    }
    transparentimage(NULL, x - 5, y - 5, &img[66]);
    if (state != bomb)
        (*Player).fbomb = 0;
}

void PlayerB::Shoot()
{
    if (GetKeyState(90) < 0 && Game1.t - t1 >= (*Player).tshoot)    //当玩家按下z键且与上次射击间隔超过攻击频率时创建一组新的子弹对象
    {
        if (Game1.power == 1)
        {
            PlayerBullet* a = new PlayerBulletB();
            end->next = a;
            end->next->BulletInit((*Player).x , (*Player).y, 0);
            end = a;

            
        }

        if (Game1.power == 2)
        {
            PlayerBullet* a = new PlayerBulletB();
            end->next = a;
            end->next->BulletInit((*Player).x , (*Player).y, 0);
            end = a;

            PlayerBullet* b = new PlayerBulletB();
            end->next = b;
            end->next->BulletInit((*Player).x + 10, (*Player).y, 0);
            end = b;

            PlayerBullet* c = new PlayerBulletB();
            end->next = c;
            end->next->BulletInit((*Player).x -10, (*Player).y,0);
            end = c;

        }

        if (Game1.power == 3)
        {
            PlayerBullet* a = new PlayerBulletB();
            end->next = a;
            end->next->BulletInit((*Player).x - 20, (*Player).y, 0);
            end = a;

            PlayerBullet* b = new PlayerBulletB();
            end->next = b;
            end->next->BulletInit((*Player).x + 20, (*Player).y, 0);
            end = b;

            PlayerBullet* c = new PlayerBulletB();
            end->next = c;
            end->next->BulletInit((*Player).x - 10, (*Player).y, 0);
            end = c;

            PlayerBullet* d = new PlayerBulletB();
            end->next = d;
            end->next->BulletInit((*Player).x + 10, (*Player).y,0);
            end = d;

        }

        if (Game1.power == 4)
        {
            PlayerBullet* a = new PlayerBulletB();
            end->next = a;
            end->next->BulletInit((*Player).x - 10, (*Player).y, 0);
            end = a;

            PlayerBullet* b = new PlayerBulletB();
            end->next = b;
            end->next->BulletInit((*Player).x + 10, (*Player).y, 0);
            end = b;

            PlayerBullet* c = new PlayerBulletB();
            end->next = c;
            end->next->BulletInit((*Player).x - 20, (*Player).y, 0);
            end = c;

            PlayerBullet* d = new PlayerBulletB();
            end->next = d;
            end->next->BulletInit((*Player).x + 20, (*Player).y, 0);
            end = d;

            PlayerBullet* e = new PlayerBulletB();
            end->next = e;
            end->next->BulletInit((*Player).x - 25, (*Player).y, 0);
            end = e;

            PlayerBullet* f = new PlayerBulletB();
            end->next = f;
            end->next->BulletInit((*Player).x + 25, (*Player).y, 0);
            end = f;
        }

        t1 = Game1.t;
    }
    //遍历所有子弹对象
    PlayerBullet* it;
    it = head;
    while (it != NULL)
    {
        it->t = (Game1.t - it->t0);   //以毫秒为单位计时
        if (it->state == alive)
        {
            it->Move();
            it->Draw();
        }
        if (it->state == dying)
        {
            it->Drawhiting();
        }
        it->Check();
        it = it->next;
    }
}

void PlayerB::Bomb()
{
    if (GetKeyState(88) < 0 && Game1.t - tbomb0 >= (*Player).tbomb && Game1.bomb > 0 && Player->state != dying)
    {
        state = bomb;
        tbomb0 = Game1.t;
        Game1.bomb--;
    }
    if (Game1.t - tbomb0 >= Player->tbomb && state == bomb)
        state = alive;
}

void PlayerBulletB::BulletInit(float x, float y, double theta)
{
    this->state = alive;
    this->x0 = x;
    this->y0 = y;
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->damage = 10;
    this->t0 = Game1.t;
    this->t = Game1.t;
}



void PlayerBulletB::Move()
{
    y = y0 - cos(theta) * t;
    x = x0 + sin(theta) * t;
    //x = x0 +80*sin(t/50);
    //y = y0 - 100*sin(30*t+30);
    //x = x0 + 100*sin(30);
}

void PlayerBulletB::Check()
{
    PlayerBullet* itt;
    if (this->next != NULL && this->next->next != NULL && (this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
    {
        itt = this->next->next;
        delete(this->next);
        this->next = itt;
    }
    /*if ( it->next != NULL && it->next->next == NULL&&(it->next->y <= 10 || it->next->x <= 370 || it->next->x >= 990) )
    {
        delete(it->next);
        it->next = NULL;
    }*/
}

void PlayerBulletB::Draw()
{
    //RotateImage(&A, &img[19], theta);    //将图片旋转一定角度
    transparentimage(NULL, this->x - 15, this->y - 200, &img[19]);
    //putimage(this->x - 15, this->y - 15, &A);
}

void PlayerBulletB::Drawhiting()
{
    int v = 100;
    if (Game1.t - this->t1 >= v)
    {
        //IMAGE* A=frame+fhit;
        transparentimage(NULL, x - 75, y - 75, &this->frame[this->fhit]);
        //putimage(x, y, &this->frame[this->fhit]);
        fhit++;
        if (fhit > hitframe - 1)
        {
            /*PlayerBullet* ittt;
            if (this != Player->head && this != Player->head->next)
            {
                ittt = this->next->next;
                if (this->next == Player->end)
                    Player->end = this;
                delete(this->next);
                this->next = ittt;
            }*/
            state = dead;
        }
        this->t1 = Game1.t;
    }
    else
    {
        transparentimage(NULL, x - 75, y - 75, &this->frame[this->fhit]);
        //putimage(x - 40, y - 40, &this->frame[this->fhit]);
    }
}
