#include "perlin_points.h"

void perlin_points::draw(sf::RenderTarget&t, sf::RenderStates s) const
{
	t.draw(points);
	t.draw(text);
}

int perlin_points::index(int i, int j)
{

	if (i < 0 || j < 0)
		return -100;
	else 
		return i  + j*cols;

}

perlin_points::perlin_points() :points(sf::Points, 120 * 120), pre_points(sf::Points, 120 * 120), cur_points(sf::Points, 120 * 120), rows(120), cols(120), width(5), height(5), noise(std::time(0))
{
	total_time = sf::seconds(0.25);
	multipliyer = 200.f;
	double xoff = (rand() % 1000) / 100000, yoff = (rand() % 1000) / 100000, xratio, yratio;
	float dir;
	xreff = (rand() % 1000) / 100000;
	yreff = (rand() % 1000) / 100000;
	xoff = xreff;

	for (int i = 1; i <= rows; i++)
	{
		xoff += 0.02;

		xratio = (60.f - abs(rows / 2 - i)) / 60.f;
		yoff = yreff;
		for (int j = 1; j <= cols; j++)
		{
			yratio = (60.f - abs(cols / 2 - j)) / (60.f);
			yoff += 0.02;
			dir = noise.noise(xoff, yoff, 0) * 2 * PI;
			cur_points[index(i - 1, j - 1)].position = pre_points[index(i - 1, j - 1)].position = points[index(i - 1, j - 1)].position = sf::Vector2f(i * 5 + cos(dir) * multipliyer * xratio, j * 5 + sin(dir) * multipliyer * yratio);

		}

	}

}

void perlin_points::update()
{
	if (total_time.asSeconds() < update_timer.getElapsedTime().asSeconds())
	{
		points = cur_points;
		pre_points = cur_points;
		update_timer.restart();
		double xoff = xreff, yoff = yreff, dir, xratio, yratio;

		for (int i = 1; i <= rows; i++)
		{
			xoff += 0.02;
			xratio = (60.f - abs(rows / 2 - i)) / (60.f);
			yoff = yreff;
			for (int j = 1; j <= cols; j++)
			{
				yoff += 0.02;
				yratio = (60.f - abs(cols / 2 - j)) / (60.f);
				dir = noise.noise(xoff, yoff, 0) * 2 * PI;
				cur_points[index(i - 1, j - 1)].position = sf::Vector2f(i * 5 + cos(dir) * multipliyer * xratio, j * 5 + sin(dir) * multipliyer * yratio);

			}

		}

		
	}
	else
	{
		double x, y, speed = update_timer.getElapsedTime().asSeconds() / total_time.asSeconds();;
		
		for (int i = 0; i < rows; i++)
		{



			for (int j = 0; j < cols; j++)
			{
				x = pre_points[index(i, j)].position.x + ((cur_points[index(i, j)].position.x - pre_points[index(i, j)].position.x) * speed);
				y = pre_points[index(i, j)].position.y + ((cur_points[index(i, j)].position.y - pre_points[index(i, j)].position.y) * speed);
				points[index(i, j)].position = sf::Vector2f(x, y);
				

			}

		}
	}
	xreff +=2 ; yreff += 2;
}

void perlin_points::change_m(int a)
{
	multipliyer += a;
}
