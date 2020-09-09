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
#include "tool.h"
#define  PI 3.14159265

extern IMAGE img[500];
extern Games Game1;
extern Players* Player;
extern Stage* stage;
extern Tools* Tool;

void Tool1::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next!=NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y>=735||this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool1::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool1::Init(float x, float y, double theta)
{
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 40;
	this->theta = theta;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool1::Function()
{
	Game1.score = Game1.score + 100;
}

void Tool1::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[59]);
	//putimage(x, y, &img[4]);
}

void Tool2::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool2::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool2::Init(float x, float y, double theta)
{
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool2::Function()
{
	Game1.score = Game1.score + 200;
}

void Tool2::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[60]);
	//putimage(x, y, &img[4]);
}

void Tool3::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool3::Move()
{
	x = x0;
	y = y0+ 0.1 * t;
}

void Tool3::Init(float x, float y, double theta)
{
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool3::Function()
{
	Game1.score = Game1.score + 300;
}

void Tool3::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[61]);
	//putimage(x, y, &img[4]);
}

void Tool4::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool4::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool4::Init(float x, float y, double theta)
{
	this->x0 =x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool4::Function()
{
	Game1.score = Game1.score + 400;
}

void Tool4::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[62]);
	//putimage(x, y, &img[4]);
}

void Tool5::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool5::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool5::Init(float x, float y, double theta)
{
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool5::Function()
{
	if (Game1.power < 4)
	{
		Game1.power = Game1.power + 1;
	}
	if (Game1.power ==4)
	{
		Game1.power = 4;
	}
}

void Tool5::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[64]);
	//putimage(x, y, &img[4]);
}

void Tool6::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool6::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool6::Init(float x, float y, double theta)
{
	srand((unsigned)time(NULL));
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool6::Function()
{
	Game1.life = Game1.life + 1;
}

void Tool6::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[65]);
	//putimage(x, y, &img[4]);
}

void Tool7::Check()
{
	float d, d1;
	Tools* it;
	Tools* itt;
	it = stage->headtool;
	itt = stage->headtool;
	if
		(this->next != NULL)
	{
		d = (Player->x - this->next->x) * (Player->x - this->next->x) + (Player->y - this->next->y) * (Player->y - this->next->y);
		d1 = sqrt(d);
		if (d1 < (Player->r + this->next->r) && this->next != NULL)
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				this->next->Function();
				delete(this->next);
				this->next = NULL;
			}
		}
		if (this->next != NULL && (this->next->y >= 735 || this->next->y <= 10 || this->next->x <= 370 || this->next->x >= 990))
		{
			if (this->next->next != NULL)
			{
				itt = this->next->next;
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = itt;
			}
			else
			{
				if (this->next == stage->endtool)
				{
					stage->endtool = this;
				}
				delete(this->next);
				this->next = NULL;
			}
		}
	}
}

void Tool7::Move()
{
	x = x0;
	y = y0 + 0.1 * t;
}

void Tool7::Init(float x, float y, double theta)
{
	this->x0 = x;
	this->y0 = y;
	this->x = x;
	this->y = y;
	this->r = 20;
	this->t0 = Game1.t;
	this->t = Game1.t;
}

void Tool7::Function()
{
	Game1.bomb = Game1.bomb + 1;
}

void Tool7::Draw()
{
	transparentimage(NULL, x-20, y-20, &img[63]);
	//putimage(x, y, &img[4]);
}
