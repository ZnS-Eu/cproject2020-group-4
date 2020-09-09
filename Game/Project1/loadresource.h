#pragma once
#include <easyx.h>
#include <conio.h>

void loadresource();	//加载图像资源
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);	//绘制半透明图像