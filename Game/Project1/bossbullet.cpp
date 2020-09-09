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
#include "bossbullet.h"
#define  PI 3.14159265

extern IMAGE img[500];
extern Games Game1;
extern Stage* stage;
extern Players* Player;


void BossBullets::BulletCheck()
{

    /*检测自机与敌机子弹的碰撞*/
    float d2, d22;
    d22 = (Player->x - this->x) * (Player->x - this->x) + (Player->y - this->y) * (Player->y - this->y);
    d2 = sqrt(d22);
    if (d2 < (Player->r + this->r) && Player->state != dying && Player->state != bomb
        && Game1.t - Player->tdead >= Player->tcantbeharmed)
    {
        Game1.life--;
        Game1.bomb = 3;
        Player->state = dying;
        Player->f = Player->dyingframe0;
    }
    float d3, d33;
    if (this->next != NULL)
    {
        d33 = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
        d3 = sqrt(d33);
    }
    /*检测消弹*/
    BossBullets* itt;
    if (this->next != NULL && this->next->next != NULL
        && (this->next->y <= 10 || this->next->x <= 370
            || this->next->x >= 990 || this->next->y >= 735
            || (Player->state == bomb && d3 <= Player->bombr)))
    {
        itt = this->next->next;
        if (this->next == stage->endbullet)
            stage->endbullet = this;
        delete(this->next);
        this->next = itt;
    }
}

/******************************************************/
/********************BossBulletA***********************/
/******************************************************/

void BossBulletA::BulletInit(float x, float y, double theta)
{
    this->alive = 0;
    this->x0 = x;
    this->y0 = y;
    this->x = x;
    this->y = y;
    this->r = 10;
    this->theta = theta;
    this->t0 = Game1.t;
    this->t = Game1.t;
}

void BossBulletA::Move()
{
    y = y0 - 0.4*cos(theta) * t;
    x = x0 + 0.4*sin(theta) * t;
}



void BossBulletA::Draw()
{
    //IMAGE A;
    //RotateImage(&A, &img[13], theta);    //将图片旋转一定角度
    //transparentimage(NULL, this->x - 15, this->y - 15, &img[13]);
    transparentimage(NULL, this->x - 20, this->y - 20, &img[68]);
    //putimage(this->x - 15, this->y - 15, &A);
}

/******************************************************/
/********************BossBulletB***********************/
/******************************************************/

void BossBulletB::BulletInit(float x, float y, double theta)
{
    this->alive = 0;
    this->x0 = x;
    this->y0 = y;
    this->x = x;
    this->y = y;
    this->r = 10;
    this->theta = theta;
    this->t0 = Game1.t;
    this->t = Game1.t;
}

void BossBulletB::Move()
{
    y = y0 - 0.08 * cos(theta) * t*t/1000;
    x = x0 + 0.08 * sin(theta) * t*t/1000;
}



void BossBulletB::Draw()
{
    //IMAGE A;
    //RotateImage(&A, &img[13], theta);    //将图片旋转一定角度
    transparentimage(NULL, this->x - 20, this->y - 20, &img[67]);
    //transparentimage(NULL, this->x - 15, this->y - 15, &img[13]);
    //putimage(this->x - 15, this->y - 15, &A);
}

/******************************************************/
/********************BossBulletC***********************/
/******************************************************/

void BossBulletC::BulletInit(float x, float y, double theta)
{
    this->alive = 0;
    this->x0 = x;
    this->y0 = y;
    this->x = x;
    this->y = y;
    this->r = 5;
    this->theta = theta;
    this->t0 = Game1.t;
    this->t = Game1.t;
}

void BossBulletC::Move()
{
    y = y0 - 0.3 * cos(theta) * t*t/1000;
    x = x0 + 0.3 * sin(theta) * t*t/1000;
}



void BossBulletC::Draw()
{
    //IMAGE A;
    //RotateImage(&A, &img[13], theta);    //将图片旋转一定角度
    //transparentimage(NULL, this->x - 15, this->y - 15, &img[68]);
    transparentimage(NULL, this->x - 15, this->y - 15, &img[13]);
    //putimage(this->x - 15, this->y - 15, &A);
}


/******************************************************/
/********************BossBulletD***********************/
/******************************************************/

void BossBulletD::BulletInit(float x, float y, double theta)
{
    this->alive = 0;
    this->x0 = x;
    this->y0 = y;
    this->x = x;
    this->y = y;
    this->r = 5;
    this->theta = theta;
    this->t0 = Game1.t;
    this->t = Game1.t;
}

void BossBulletD::Move()
{
    y = y0 - 0.4 * cos(theta) * t;
    x = x0 + 0.4 * sin(theta) * t;
}



void BossBulletD::Draw()
{
    //IMAGE A;
    //RotateImage(&A, &img[13], theta);    //将图片旋转一定角度
    //transparentimage(NULL, this->x - 15, this->y - 15, &img[68]);
    transparentimage(NULL, this->x - 12.5, this->y - 12.5, &img[126]);
    //putimage(this->x - 15, this->y - 15, &A);
}