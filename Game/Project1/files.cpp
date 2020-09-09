#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include "game.h"
#include "loadresource.h"
#include "player.h"
#include "stage.h"
#include "boss.h"
#include <stdio.h>
#include <time.h>
extern class Games Game1;

void Games::Writedata()
{
	int i = 0;
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "./data.dat", "a");

	int j = 0;
	/*for (j = 0; j < 100; j++)
	{
		play[i].name[j] = Game1.Name[j];
	}*/

	time(&now);
	Game1.date = localtime(&now);
	fprintf_s(fp,"%d/%d/%d %02d:%02d:%02d ",
		Game1.date->tm_year + 1900, Game1.date->tm_mon + 1, Game1.date->tm_mday, Game1.date->tm_hour, Game1.date->tm_min, Game1.date->tm_sec);
	/*for (j = 0; j < 100; j++)
	{
		play[i].date[j] = Game1.date[j];
	}*/
	play[i].score = Game1.score;
	play[i].life = Game1.life;

	fprintf_s(fp, "%d %d\n", play[i].score, play[i].life);
	//fprintf_s(fp, "%s %d %d\n", play[i].name, play[i].score, play[i].life);
	//fprintf_s(fp, "%s\n", play[i].name);
	fclose(fp);

}

//err = fopen_s(&fp, "./data.txt", "w+");

void Games::Readdata()
{
	int i = 0;
	FILE* fp;
	fp = fopen( "./data.dat", "r");
	int j = 0;
	int k = 0;
	int temp;
	int tmp;
	for (i = 0; i < 100; i++)
	{
		//fscanf(fp, "%s %d %d\n", play[i].name, &(play[i].score), &(play[i].life));
		//fscanf(fp, "%s ", play[i].name);
		fscanf(fp, "%d/%d/%d %02d:%02d:%02d ",
			&(play[i].date.year), &(play[i].date.month), &(play[i].date.day), &(play[i].date.hour), &(play[i].date.minute), &(play[i].date.second));
		//for (i = 0; i < 10; i++)
		fscanf(fp, "%d ", &(play[i].score));
		fscanf(fp, "%d\n", &(play[i].life));
		//fgets(play[i].name, 50, fp);
	}
	for (i = 0; i < 100; i++)
	{
		for (j = i+1; j < 100; j++)
		{
			if (play[j].score > play[i].score)
			{
				temp = play[i].score;
				play[i].score = play[j ].score;
				play[j ].score = temp;
				/*for (k = 0; k < 100; k++)
				{
					tmp = play[i].name[k];
					play[i].name[k] = play[j].name[k];
					play[j].name[k] = tmp;
				}*/
				tmp = play[i].date.year;
				play[i].date.year = play[j].date.year;
				play[j].date.year = tmp;

				tmp = play[i].date.month;
				play[i].date.month = play[j].date.month;
				play[j].date.month = tmp;

				tmp = play[i].date.day;
				play[i].date.day = play[j].date.day;
				play[j].date.day = tmp;

				tmp = play[i].date.hour;
				play[i].date.hour = play[j].date.hour;
				play[j].date.hour = tmp;

				tmp = play[i].date.minute;
				play[i].date.minute = play[j].date.minute;
				play[j].date.minute = tmp;

				tmp = play[i].date.second;
				play[i].date.second = play[j].date.second;
				play[j].date.second = tmp;

				temp = play[i].life;
				play[i].life = play[j].life;
				play[j].life = temp;
			}
		}
	}
	/*for (i = 0; i <= 10; i++)
		fscanf_s(fp, "%s %d %d\n", play[i].name,  (play[i].score), (play[i].life));*/
	fclose(fp);

}
