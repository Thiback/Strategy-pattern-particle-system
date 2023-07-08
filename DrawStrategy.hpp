#ifndef DRAW_STRATEGY_HPP
#define DRAW_STRATEGY_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class DrawStrategy {
public:
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position, float size) = 0;
};

class SpriteDrawStrategy: public DrawStrategy {

	std::vector<sf::Sprite *> &sprites;
	unsigned int current_sprite_index;

public:
	SpriteDrawStrategy(std::vector<sf::Sprite *> &sprites, unsigned int current_sprite_index): sprites(sprites) {
		this->current_sprite_index = current_sprite_index;
		std::cout << "current_sprite_index " << current_sprite_index << std::endl;
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		sf::Sprite* current_sprite = this->sprites[current_sprite_index];

		current_sprite->setPosition(position);
		current_sprite->setScale({ size, size });
		window.draw(*(current_sprite));
	};
};


class TextDrawStrategy : public DrawStrategy {

	sf::Text* txt = nullptr;
	std::string content;

public:

	TextDrawStrategy(sf::Text* text, std::string content) {
		this->txt = text;
		this->content = content;
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		this->txt->setPosition(position);
		this->txt->setCharacterSize(size * 20);
		this->txt->setFillColor(sf::Color::Yellow);
		this->txt->setString(this->content);
		window.draw(*(this->txt));
	}
};


class DotDrawStrategy : public DrawStrategy {

	sf::Color colors[7] = {
		sf::Color::White,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Cyan
	};

	sf::CircleShape* dot;
	sf::Color color;

public:
	DotDrawStrategy(sf::CircleShape* circle) {
		this->dot = circle;
		this->color = this->colors[rand() % 7];
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		this->dot->setPosition(position);
		this->dot->setRadius(size * 10);
		this->dot->setFillColor(this->color);
		window.draw(*(this->dot));
	}
};

#endif