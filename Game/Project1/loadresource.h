#pragma once
#include <easyx.h>
#include <conio.h>

void loadresource();	//����ͼ����Դ
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);	//���ư�͸��ͼ��