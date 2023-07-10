#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawStrategy.hpp"

class Particle {

	sf::Vector2f position;
	float size;
	DrawStrategy* draw_strat = nullptr;
	sf::Vector2f velocity; // pixels per second
	sf::Clock move_clock;

public:
	
	Particle(Particle& p) = delete;

	Particle(sf::Vector2f position, float size, sf::Vector2f velocity) : position(position), size(size), velocity(velocity) {};

	void draw(sf::RenderWindow& window) {
		this->draw_strat->draw(window, this->position, this->size);
	};

	void update() {

		float elapsed_seconds = this->move_clock.getElapsedTime().asSeconds();
		
		this->position += this->velocity * elapsed_seconds;
		this->draw_strat->update();
		this->move_clock.restart();
	}

	void setDrawStrategy(DrawStrategy* draw_strat) {
		if (this->draw_strat) delete this->draw_strat;
		this->draw_strat = draw_strat;
	}

	sf::Vector2f getPosition() {
		return this->position;
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;
	}
	
	float getSize() {
		return this->size;
	}
};
#endif