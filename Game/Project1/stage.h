#pragma once
#include "boss.h"
#include "bossbullet.h"
#include "tool.h"

class Stage
{
public:
	bool clear;
	float x;
	float y;
	long t0;
	long t;
	long tclear;
	long tim[40];		//boss����ʱ��
	long tim2[70];//���߳��ֵ�ʱ��
	Boss* headboss;		//ָ��boss�����ͷָ��
	Boss* endboss;
	BossBullets* headbullet;	//ָ��boss�ӵ���ָ��
	BossBullets* endbullet;
	Tools* headtool;	//ָ����������ͷָ��
	Tools* endtool;
	
	virtual void Createstage()=0;
	virtual void Clearstage()=0;
	virtual void Createboss()=0;
	virtual void Creattool() = 0;
	virtual void Draw()=0;
	virtual void Drawprestage()=0;
};

class Stage1 : public Stage
{
public:
	void Createstage();
	void Clearstage();
	void Createboss();
	void Creattool();
	void Draw();
	void Drawprestage();
};

class Stage2 : public Stage
{
public:
	void Createstage();
	void Clearstage();
	void Createboss();
	void Creattool();
	void Draw();
	void Drawprestage();
};

class Stage3 : public Stage
{
public:
	void Createstage();
	void Clearstage();
	void Createboss();
	void Creattool();
	void Draw();
	void Drawprestage();
};

