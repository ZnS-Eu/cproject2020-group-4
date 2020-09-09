#include "loadresource.h"
#include <math.h>
#define PI 3.14159265
#pragma comment( lib, "MSIMG32.LIB")

IMAGE img[500];

void loadresource()
{
	int m;
	for (m = 0; m < 200; m++)
	{
		img[m] = NULL;
	}
	int i = 0;
	//loadimage(&img[0], _T("Resources\\title00.jpg"));
	//loadimage(&img[1], _T("Resources\\title01.jpg"));
	//loadimage(&img[2], _T("Resources\\title02.jpg"));
	loadimage(&img[3], _T("Resources\\background.png"));
	loadimage(&img[4], _T("Resources\\playera.png"));
	loadimage(&img[5], _T("Resources\\pause00.png"));
	loadimage(&img[6], _T("Resources\\pause01.png"));
	loadimage(&img[7], _T("Resources\\pause02.png"));
	loadimage(&img[8], _T("Resources\\playera01.png"));
	loadimage(&img[9], _T("Resources\\playera02.png"));
	loadimage(&img[10], _T("Resources\\playera03.png"));
	loadimage(&img[11], _T("Resources\\playera04.png"));
	loadimage(&img[12], _T("Resources\\stage1background01.jpg"));
	loadimage(&img[13], _T("Resources\\bulleta00.png"));
	loadimage(&img[14], _T("Resources\\playerselect00.png"));
	loadimage(&img[15], _T("Resources\\playerselect01.png"));
	loadimage(&img[16], _T("Resources\\playerselect02.png"));
	loadimage(&img[17], _T("Resources\\playerselect03.png"));
	loadimage(&img[18], _T("Resources\\bulletb00.png"));
	loadimage(&img[19], _T("Resources\\bulletc00.png"));
	for (i = 0; i < 10; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\explosiona%02d.png"), i);
		loadimage(&img[i+20], filename);
	}
	for (i = 0; i < 20; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\bomba%02d.png"), i);
		loadimage(&img[i + 30], filename);
	}
	for (i = 0; i < 9; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\prestagea%02d.png"), i);
		loadimage(&img[i + 50], filename);
	}
	for (i = 0; i < 7; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\tool%02d.png"), i);
		loadimage(&img[i + 59], filename);
	}
	loadimage(&img[66], _T("Resources\\collisionpoint.png"));
	loadimage(&img[67], _T("Resources\\bulletd00.png"));
	loadimage(&img[68], _T("Resources\\bullete00.png"));
	for (i = 0; i < 5; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\title%02d.png"), i);
		loadimage(&img[i + 69], filename);
	}
	for (i = 0; i < 13; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\explosionb%02d.png"), i);
		loadimage(&img[i + 74], filename);
	}
	loadimage(&img[87], _T("Resources\\ending.png"));
	for (i = 0; i < 8; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\bossa%02d.png"), i);
		loadimage(&img[i + 88], filename);
	}
	loadimage(&img[96], _T("Resources\\bossb.png"));
	for (i = 0; i < 12; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\bossg%02d.png"), i);
		loadimage(&img[i + 97], filename);
	}
	for (i = 0; i < 15; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\bossh%02d.png"), i);
		loadimage(&img[i + 109], filename);
	}
	loadimage(&img[124], _T("Resources\\bossf.png"));
	loadimage(&img[125], _T("Resources\\bosse.png"));
	loadimage(&img[126], _T("Resources\\bulletf.png"));
	for (i = 0; i < 29; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\explosionc%02d.png"), i);
		loadimage(&img[i + 127], filename);
	}
	for (i = 0; i < 14; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\STAGE1\\stagea%02d.png"), i);
		loadimage(&img[i + 156], filename);
	}
	for (i = 0; i < 14; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\STAGE2\\stageb%02d.png"), i);
		loadimage(&img[i + 170], filename);
	}
	for (i = 0; i < 14; i++)
	{
		TCHAR filename[100];
		_stprintf_s(filename, _T("Resources\\STAGE3\\stagec%02d.png"), i);
		loadimage(&img[i + 184], filename);
	}
	loadimage(&img[198], _T("Resources\\playerdata.png"));
	loadimage(&img[199], _T("Resources\\life.png"));
	loadimage(&img[200], _T("Resources\\bomb.png"));
}

void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad)
{
	IMAGE* pWorking = GetWorkingImage();
	SetWorkingImage(pFrom);
	int iWidth = getwidth();
	int iHeight = getheight();												// 获取原图长宽

	while (rad > 2 * PI)													// 化简弧度
		rad -= 2 * PI;

	double pad = rad;														// 处理弧度
	if (pad > PI / 2 && pad <= PI)
	{
		pad -= PI / 2;
		pad = PI / 2 - pad;
	}
	else if (pad > PI && pad <= PI / 2 * 3)
	{
		pad -= PI;
	}
	else if (pad > PI / 2 * 3 && pad <= PI * 2)
	{
		pad -= PI / 2 * 3;
		pad = PI / 2 - pad;
	}

	int	tWidth = int(iWidth * cos(pad) + iHeight * sin(pad));
	int	tHeight = int(iHeight * cos(pad) + iWidth * sin(pad));				// 计算新图大小

	int iMinX = -(iWidth / 2), iMinY = -(iHeight / 2);
	int iMaxX = iMinX + iWidth, iMaxY = iMinY + iHeight;					// 计算原图最小（大）坐标

	int tMinX = -(tWidth / 2), tMinY = -(tHeight / 2);
	int tMaxX = tMinX + tWidth, tMaxY = tMinY + tHeight;					// 计算新图最小（大）坐标

	setorigin(-iMinX, -iMinY);												// 设置图片中心为原点

	SetWorkingImage(NULL);
	pTo->Resize(tWidth, tHeight);											// 初始化新图

	DWORD* dst = GetImageBuffer(pTo);
	DWORD* src = GetImageBuffer(pFrom);										// 获取新图、原图的缓冲区

	SetWorkingImage(pTo);
	for (int y1 = 0; y1 < tHeight; y1++)
	{
		for (int x1 = 0; x1 < tWidth; x1++)
			dst[x1] = 0x00000000;
		dst += tWidth;
	}
	SetWorkingImage(pWorking);
	for (int y1 = 0; y1 < tHeight; y1++)									// 初始化新图
		dst -= tWidth;

	for (int y1 = tMinY; y1 < tMaxY; y1++)
	{
		for (int x1 = tMinX; x1 < tMaxX; x1++)
		{
			int x = int(x1 * cos(rad) - y1 * sin(rad));
			int y = int(x1 * sin(rad) + y1 * cos(rad));						// 计算变换后坐标

			int sxy = (iHeight - (y - iMinY) - 1) * iWidth + (x - iMinX);
			int dxy = (tHeight - (y1 - tMinY) - 1) * tWidth + (x1 - tMinX);	// 计算坐标在缓冲区的位置

			if (x >= iMinX && x < iMaxX && y >= iMinY && y < iMaxY)			// 越界特判
				dst[dxy] = src[sxy];
		}
	}

	SetWorkingImage(pFrom);
	setorigin(0, 0);
	SetWorkingImage(pWorking);												// 还原原图坐标
}

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);

	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}//from codeabc 慢羊羊的空间


