#include "boxes.h"


float b_width = (20.f);
float b_height = (20.f);
float w_width = 800;
float w_height = 800;
float rows = w_width / b_width;
float cols = w_height / b_height;

boxes::boxes() :current(0, 0), current_colour(255, 0, 0, 255)
{
	color_var = new int[3];
	color_var[0] = 0;
	color_var[1] = 1;
	color_var[2] = 0;
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			lines l(i * b_width, j * b_height);
			cells.push_back(l);
		}
	}
	cells[0].setvisit_true();
	stack.push_back(cells[0]);
}

void boxes::render(sf::RenderTarget& t)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)

			t.draw(cells[int(index(i, j))]);
	}

}

void boxes::update_()
{
	// random neibor;
	lines n = check_neibors(current);
	int i, j;
	if ((n.getindex_i() < 0 || n.getindex_j() < 0) && stack.size()>1)
	{
		
		n = stack[stack.size()-1];
		stack.pop_back();
		i = n.getindex_i(), j = n.getindex_j();
		cells[index(current.x, current.y)].set_box_color(sf::Color(100,255,100,200));
		current.x = stack[stack.size() - 1].getindex_i();
		current.y = stack[stack.size() - 1].getindex_j();
		//current_colour = cells[index(current.x, current.y)].precolor();
		cells[index(current.x, current.y)].set_box_color(sf::Color(255, 0, 100, 255),color_var);//current cell;
		//color_var=cells[index(current.x, current.y)].getcval();
	}
	else if(n.getindex_i()>=0&&n.getindex_j()>=0)
	{
		//upcolor();
	
		i = n.getindex_i(), j = n.getindex_j();
		removewalls(current, sf::Vector2i(i, j));
		cells[index(i, j)].setvisit_true();
		cells[index(current.x, current.y)].set_box_color(sf::Color(100,255,100,200));
		cells[index(i, j)].set_box_color(sf::Color(255, 0, 100, 255),color_var);//current cell
		
		current.x = i, current.y = j;
		stack.push_back(cells[index(i, j)]);

	}
}
lines boxes::check_neibors(sf::Vector2i ind)
{
	int i = ind.x, j = ind.y;

	vector<lines> neibors;
	vector<bool> s(4);
	lines top, right, bottom, left;
	s[0] = index(i, j - 1) >= 0 && !cells[index(i, j - 1)].if_visited();
	s[1] = index(i + 1, j) >= 0 && !cells[index(i + 1, j)].if_visited();
	s[2] = index(i, j + 1) >= 0 && !cells[index(i, j + 1)].if_visited();
	s[3] = index(i - 1, j) >= 0 && !cells[index(i - 1, j)].if_visited();
	
	if (s[0])
	{
		top = cells[index(i, j - 1)];
		neibors.push_back(top);
		
	}
	if (s[1])
	{
		right = cells[index(i + 1, j)];
		neibors.push_back(right);
		
	}
	if (s[2])
	{
		bottom = cells[index(i, j + 1)];
		neibors.push_back(bottom);
		
	}
	if (s[3])
	{
		left = cells[index(i - 1, j)];
		neibors.push_back(left);
		
	}
	
	if (neibors.size() != 0)
	{
		int n = rand() % neibors.size();
		return neibors[n];
	}
	else
		return lines(-100,-100);
}

int boxes::index(int i, int j)
{
	if (i < 0 || j < 0 || i >= rows || j >= cols)
		return -1;
	else
		return int(i * rows + j);
}

void boxes::removewalls(sf::Vector2i current, sf::Vector2i next)
{
	int i = current.x - next.x, j = current.y - next.y;
	if (i == 1)
	{
		cells[index(current.x, current.y)].removewalls(side_pos::left);
		cells[index(next.x, next.y)].removewalls(side_pos::right);
	}
	else if (i == -1)
	{
		cells[index(current.x, current.y)].removewalls(side_pos::right);
		cells[index(next.x, next.y)].removewalls(side_pos::left);
	}
	if (j == 1)
	{
		cells[index(current.x, current.y)].removewalls(side_pos::top);
		cells[index(next.x, next.y)].removewalls(side_pos::bottom);
	}
	else if (j == -1)
	{
		cells[index(current.x, current.y)].removewalls(side_pos::bottom);
		cells[index(next.x, next.y)].removewalls(side_pos::top);
	}

}

void boxes::upcolor()
{
	current_colour.r += color_var[0];
	current_colour.g += color_var[1];
	current_colour.b += color_var[2];
	
	if (current_colour.r == 255 && current_colour.g == 0 && current_colour.b == 0)
	{
		color_var[2] = 0;
		color_var[1] = 1;
		color_var[0] = 0;
	}
	else if (current_colour.r == 255 && current_colour.g == 255 && current_colour.b == 0)
	{
		color_var[1] = 0;
		color_var[0] = -1;
		color_var[2] = 0;
	}
	else if (current_colour.r == 0 && current_colour.g == 255 && current_colour.b == 0)
	{
		color_var[2] = 1;
		color_var[0] = 0;
		color_var[1] = 0;
	}
	else if (current_colour.r == 0 && current_colour.g == 255 && current_colour.b == 255)
	{
		color_var[1] = -1;
		color_var[2] = 0;
		color_var[0] = 0;
	}
	else if (current_colour.r == 0 && current_colour.g == 0 && current_colour.b == 255)
	{
		color_var[1] = 0;
		color_var[0] = 1;
		color_var[2] = 0;
	}
	else if (current_colour.r == 255 && current_colour.g == 0 && current_colour.b == 255)
	{
		color_var[1] = 1;
		color_var[0] = 0;
		color_var[2] = 0;
	}
	if (current_colour.r == 255 && current_colour.g == 255 && current_colour.b == 255)
	{
		color_var[1] = -1;
		color_var[2] = -1;
		color_var[0] = 0;
	}
}




















void lines::draw(sf::RenderTarget&t, sf::RenderStates s) const
{
	t.draw(square);
	for (int i = 0; i < 4; i++)
	{
		if (sides[i])
			t.draw(L[i]);
	}
}

lines::lines(float x,float y):L(4)//L(sf::Lines,8)
{
	
	index_i = int(x / b_width);
	index_j = int(y / b_height);
	for (int i = 0; i < 4; i++)
	{
		L[i]=sf::VertexArray(sf::Lines, 2);
	}
	sides[side_pos::top] = sides[side_pos::right] = sides[side_pos::left] = sides[side_pos::bottom] = true;
	L[0][0].position = L[3][1].position = sf::Vector2f(x			,	y);
	L[0][1].position = L[1][0].position = sf::Vector2f(x + b_width,	y);
	L[1][1].position = L[2][0].position = sf::Vector2f(x + b_width,	y + b_height);
	L[2][1].position = L[3][0].position = sf::Vector2f(x			,	y + b_height);
	square.setSize(sf::Vector2f(b_width, b_height));
	square.setPosition(x, y);
	square.setFillColor(sf::Color::Black);
	visited = false;
	
}

lines::lines()
{
	index_i = -100;
	index_j = -100;
}

void lines::removewalls(side_pos p)
{
	sides[p] = false;
}

void lines::setvisit_true()
{
	
	visited = true;
	square.setFillColor(sf::Color(255, 0, 100, 100));
}

bool lines::if_visited()
{
	return visited;
}

void lines::set_box_color(sf::Color c,int a[3])
{
	r = a[0], b = a[2], g = a[1];
	cell_color = c;
	square.setFillColor(c);
}

void lines::set_box_color(sf::Color c)
{
	square.setFillColor(c);
}

int lines::getindex_i()
{
	return index_i;
}

int lines::getindex_j()
{
	return index_j;
}

/*int* lines::getcval()
{
	int a[3] = { r,g,b };
	return a;
}*/

sf::Color lines::precolor()
{
	return cell_color;
}




