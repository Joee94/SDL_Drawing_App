#include "Fill.h"

Fill::Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos)
{
	newColour = getpixel(s, 275, 25);
	oldColour = getpixel(s, pos.x, pos.y);
	std::queue<Vec2> q;

	if (newColour == oldColour)
	{
		return;
	}

	q.push(pos);
	while (!q.empty())
	{
		Vec2 n = q.front();
		q.pop();


		if (getpixel(s, n.x, n.y) == oldColour && (!checkPixelProcessed(Vec2(n.x, n.y))))
		{
			//std::cout << getpixel(s, n.x, n.y) << std::endl;
			points.push_back(n);

			if (!checkPixelProcessed(Vec2(n.x + 1, n.y)))
			{
				q.push(Vec2(n.x + 1, n.y));
			}
			if (!checkPixelProcessed(Vec2(n.x - 1, n.y)))
			{
				q.push(Vec2(n.x - 1, n.y));
			}
			if (!checkPixelProcessed(Vec2(n.x, n.y + 1)))
			{
				q.push(Vec2(n.x, n.y + 1));
			}
			if (!checkPixelProcessed(Vec2(n.x, n.y - 1)))
			{
				q.push(Vec2(n.x, n.y - 1));
			}
		}
		else {
			//std::cout << "FOUND NON ORIG COLOR PIXEL!!!" << std::endl;
		}
	}
}

Fill::~Fill()
{
}

void Fill::Colour(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

bool Fill::checkPixelProcessed(Vec2& n)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (points.at(i).Equals(n)) {
			std::cout << "ALREADY PROCESSED PIXEL FOUND!!" << std::endl;
			return true;
		}
	}

	return false;
}

void Fill::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if (!points.empty())
	{
		for (int i = 0; i < points.size(); ++i)
		{
			SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
		}
	}	
}

unsigned int Fill::getpixel(SDL_Surface *s, int x, int y)
{
	return ((unsigned int*)s->pixels)[y*(s->pitch / sizeof(unsigned int)) + x];
}

//Getting some colours
uint8_t Fill::GetR()
{
	return (this->r);
}
uint8_t Fill::GetG()
{
	return (this->g);
}
uint8_t Fill::GetB()
{
	return (this->b);
}
uint8_t Fill::GetA()
{
	return (this->a);
}