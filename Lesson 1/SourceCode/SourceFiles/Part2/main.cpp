#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(13, 20, 80, 40, image, red);
	image.flip_vertically(); //使图像原点坐标位于图片左下角
	image.write_tga_file("output.tga");
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color)
{
	//for (float t = 0; t < 1.0f; t += 0.01f)
	//{
	//	int x = static_cast<int>(x0 + (x1 - x0) * t);
	//	int y = static_cast<int>(y0 + (y1 - y0) * t);
	//	image.set(x, y, color);
	//}
	for (int x = x0; x <= x1; x++)
	{
		float t = static_cast<float>(x - x0) / static_cast<float>(x1 - x0);
		int y = static_cast<int>(y0 * (1.0f - t) + y1 * t);
		image.set(x, y, color);
	}
}
