#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawStrategy.hpp"

class Particle {

	float x;
	float y;
	float size;
	DrawStrategy* draw_strat = nullptr;
	sf::Vector2f velocity;

public:
	
	Particle(Particle& p) = delete;

	Particle(float x, float y, float size) : x(x), y(y), size(size) {};

	void draw(sf::RenderWindow& window) {
		this->draw_strat->draw(window, { this->x, this->y }, this->size);
	};

	void setDrawStrategy(DrawStrategy* draw_strat) {
		if (this->draw_strat) delete this->draw_strat;
		this->draw_strat = draw_strat;
	}
};
/*
	 set position
*/
#endif