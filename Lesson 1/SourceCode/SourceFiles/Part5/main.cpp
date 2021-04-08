#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color, bool steep);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	line(13, 20, 80, 40, image, red, false);
	line(20, 13, 40, 80, image, red, false);
	line(80, 40, 13, 20, image, white, false);
	image.flip_vertically(); //使图像原点坐标位于图片左下角
	image.write_tga_file("output.tga");
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color, bool steep)
{
	//若|y|>|x|则递归反转，否则跳转到下一步
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		line(y0, x0, y1, x1, image, color, true);
		return;
	}

	//如果目标点大于起始点则递归反转X轴，否则直接跳到下一步
	if (x0 > x1)
	{
		line(x1, y1, x0, y0, image, color, steep);
		return;
	}

	//计算误差delta
	int dx = x1 - x0;
	int dy = y1 - y0;
	//只是做了一下数学上的等价替代，效率也提升了
	int derror2 = abs(dy) * 2;
	float error2 = 0;
	int y = y0;
	//采用临时变量保存多次调用的值
	//const int yIncrease = y1 > y0 ? 1 : -1;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			image.set(y, x, color);
		else
			image.set(x, y, color);
		error2 += derror2;
		//若误差值大于一个像素，故y轴值增大或减小一个像素，对应误差值减少一
		if (error2 > dx)
		{
			//这一块的东西其实也可以挪出来
			y += y1 > y0 ? 1 : -1;
			error2 -= dx * 2;
		}
	}
}
