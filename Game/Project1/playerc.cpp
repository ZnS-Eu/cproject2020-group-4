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

void PlayerC::Init()
{
    state = alive;
    x = 680;
    y = 550;
    r = 0;
    v = 0;
    vmax = 5;
    vmin = 2.5;

    head = new PlayerBulletC;
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

void PlayerC::Move()
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


void PlayerC::Draw(long t)
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

void PlayerC::Shoot()
{
    if (GetKeyState(90) < 0 && Game1.t - t1 >= (*Player).tshoot)    //当玩家按下z键且与上次射击间隔超过攻击频率时创建一组新的子弹对象
    {
        if (Game1.power == 1)
        {
            PlayerBulletC* a = new PlayerBulletC();          
            end->next = a;
            end->next->BulletInit((*Player).x , (*Player).y, 0);
            end = a;

            PlayerBulletC* b = new PlayerBulletC();
            end->next = b;
            end->BulletInit((*Player).x  -10, (*Player).y, PI / 12);
            end = b;

            PlayerBulletC* c = new PlayerBulletC();
            end->next = c;
            end->BulletInit((*Player).x, (*Player).y, 23 * PI / 12);
            end = c;
        }

        if (Game1.power == 2)
        {
            PlayerBulletC* a = new PlayerBulletC();
            end->next = a;
            end->next->BulletInit((*Player).x, (*Player).y, 0);
            end = a;

            PlayerBulletC* b = new PlayerBulletC();
            end->next = b;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 15);
            end = b;


            PlayerBulletC* e = new PlayerBulletC();
            end->next = e;
            end->next->BulletInit((*Player).x, (*Player).y, 29 * PI / 15);
            end = e;

            PlayerBulletC* c = new PlayerBulletC();
            end->next = c;
            end->next->BulletInit((*Player).x, (*Player).y, 19 * PI / 10);
            end = c;

            PlayerBulletC* d = new PlayerBulletC();
            end->next = d;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 10);
            end = d;
        }


        

        if (Game1.power == 3)
        {
            PlayerBulletC* a = new PlayerBulletC();
            end->next = a;
            end->next->BulletInit((*Player).x, (*Player).y, 0);
            end = a;

            PlayerBulletC* b = new PlayerBulletC();
            end->next = b;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 9);
            end = b;

            PlayerBulletC* f = new PlayerBulletC();
            end->next = f;
            end->next->BulletInit((*Player).x, (*Player).y, 17 * PI / 9);
            end = f;

            PlayerBulletC* c = new PlayerBulletC();
            end->next = c;
            end->next->BulletInit((*Player).x, (*Player).y, 23 * PI / 12);
            end = c;

            PlayerBulletC* d = new PlayerBulletC();
            end->next = d;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 12);
            end = d;

            PlayerBulletC* e = new PlayerBulletC();
            end->next = e;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 18);
            end = e;

            PlayerBulletC* g = new PlayerBulletC();
            end->next = g;
            end->next->BulletInit((*Player).x, (*Player).y, 35 * PI / 18);
            end = g;

        }

        if (Game1.power == 4)
        {
            PlayerBulletC* a = new PlayerBulletC();
            end->next = a;
            end->next->BulletInit((*Player).x, (*Player).y, 0);
            end = a;

            PlayerBulletC* b = new PlayerBulletC();
            end->next = b;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 36);
            end = b;

            PlayerBulletC* c = new PlayerBulletC();
            end->next = c;
            end->next->BulletInit((*Player).x, (*Player).y, 71 * PI / 36);
            end = c;

            PlayerBulletC* d = new PlayerBulletC();
            end->next = d;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 18);
            end = d;

            PlayerBulletC* e = new PlayerBulletC();
            end->next = e;
            end->next->BulletInit((*Player).x, (*Player).y, 35 * PI / 18);
            end = e;

            PlayerBulletC* f = new PlayerBulletC();
            end->next = f;
            end->next->BulletInit((*Player).x - 10, (*Player).y, PI / 9);
            end = f;

            PlayerBulletC* g = new PlayerBulletC();
            end->next = g;
            end->next->BulletInit((*Player).x, (*Player).y, 17 * PI / 9);
            end = g;

            PlayerBulletC* h = new PlayerBulletC();
            end->next = h;
            end->next->BulletInit((*Player).x - 10, (*Player).y, 5 * PI / 36);
            end = h;

            PlayerBulletC* i = new PlayerBulletC();
            end->next = i;
            end->next->BulletInit((*Player).x, (*Player).y, 67 * PI / 36);
            end = i;

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

void PlayerC::Bomb()
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

void PlayerBulletC::BulletInit(float x, float y, double theta)
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



void PlayerBulletC::Move()
{
    y = y0 - cos(theta) * t;
    x = x0 + sin(theta) * t;
    //x = x0 +80*sin(t/50);
    //y = y0 - 100*sin(30*t+30);
    //x = x0 + 100*sin(30);
}

void PlayerBulletC::Check()
{
    PlayerBullet* itt;
    if (this->next != NULL && this->next->next != NULL && (this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
    {
        itt = this->next->next;
        delete(this->next);
        this->next = itt;
    }
    /*if (this->next != NULL && this->next->next == NULL && (this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
    {
        delete(this->next);
        this->next = NULL;
    }
    if (this==Player->head&&Player->head!=NULL&& (this->y <= 10 || this->x <= 370 || this->x >= 990))
    {
        delete(this);
        Player->head = NULL;
    }*/
    /*if ( it->next != NULL && it->next->next == NULL&&(it->next->y <= 10 || it->next->x <= 370 || it->next->x >= 990) )
    {
        delete(it->next);
        it->next = NULL;
    }*/
}

void PlayerBulletC::Draw()
{
    IMAGE A;
    RotateImage(&A, &img[18], theta);    //将图片旋转一定角度
    transparentimage(NULL, this->x - 15, this->y - 15, &A);
    //theta = theta + PI / 12;
    //putimage(this->x - 15, this->y - 15, &A);
}

void PlayerBulletC::Drawhiting()
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

