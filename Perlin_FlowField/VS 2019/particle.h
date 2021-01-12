#pragma once
#include"PerlinNoise.h"
#include<iostream>
#include<cmath>
#include<sstream>
#include<SFML/Graphics.hpp>
#define Pi 3.14159265
using namespace std;


class particle:public sf::Drawable
{
	sf::VertexArray particles, lines;
	vector<sf::CircleShape> circles;
	float speed;
	vector<sf::Vector2f> direction;
	
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
public:
	void resetparts();
	particle();
	void update(vector<float>);
	sf::Vector2f getposition(int i);
	void setdirection(sf::Vector2f,int);
	

};
