#pragma once
#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"PerlinNoise.h"
#define PI 3.14
using namespace std;
class perlin_points:public sf::Drawable
{
	sf::Text text;
	sf::Font font;
	sf::Clock update_timer;
	sf::Time total_time;

	int rows, cols,width,height,multipliyer;
	double xreff, yreff;
	sf::VertexArray points,pre_points,cur_points;
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	int index(int i, int j);
	PerlinNoise noise;
	
public:
	void change_m(int a);
	perlin_points();
	void update();
};

