#include "tgaimage.h"
#include "model.h"

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
Model *model = NULL;

const int width = 800;
const int height = 800;
void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);

int main(int argc, char** argv) {
	model = new Model("obj/african_head.obj");
	TGAImage image(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++) {
		vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = static_cast<int>((v0.x + 1.0f)*width  / 2.0f);
			int y0 = static_cast<int>((v0.y + 1.0f)*height / 2.0f);
			int x1 = static_cast<int>((v1.x + 1.0f)*width  / 2.0f);
			int y1 = static_cast<int>((v1.y + 1.0f)*height / 2.0f);
			line(x0, y0, x1, y1, image, white);
		}
	}
	image.flip_vertically(); //使图像原点坐标位于图片左下角
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color)
{
	bool steep = false;
	//若|y|>|x|则反转，否则跳转到下一步
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}


	//如果目标点大于起始点则反转X轴，否则直接跳到下一步
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	//计算误差delta
	int dx = x1 - x0;
	int dy = y1 - y0;
	//只是做了一下数学上的等价替代，效率也提升了
	int derror2 = abs(dy) * 2;
	float error2 = 0;
	int y = y0;
	//采用临时变量保存多次调用的值
	const int yIncrease = y1 > y0 ? 1 : -1;
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
			y += yIncrease;
			error2 -= dx * 2;
		}
	}
}
