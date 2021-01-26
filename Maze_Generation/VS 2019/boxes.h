#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>

   
using namespace std;
    

extern float b_width, b_height, rows, cols, w_height, w_width;
enum side_pos { top , right, bottom, left };

class lines:public sf::Drawable
{
	
	vector<sf::VertexArray> L;
	bool sides[4];
	sf::RectangleShape square;
	sf::Color cell_color;
	bool visited;
	int index_i, index_j,r,b,g;
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
public:
	lines(float x,float y);
	lines();
	void removewalls(side_pos);
	void setvisit_true();
	bool if_visited();
	void set_box_color(sf::Color,int a[3]);
	void set_box_color(sf::Color);
	int getindex_i();
	int getindex_j();
	int* getcval();
	sf::Color precolor();

	
	


};
class boxes
{
	sf::Color current_colour;
	int *color_var;
	sf::Vector2i current;
	lines check_neibors(sf::Vector2i);
	vector<class lines> cells, stack;
	
	int index(int, int);
	int tempi, tempj;
	void removewalls(sf::Vector2i,sf::Vector2i);
	void upcolor();
public:
	boxes();
	void render(sf::RenderTarget& t);
	void update_();

};