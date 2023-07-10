#ifndef DRAW_STRATEGY_HPP
#define DRAW_STRATEGY_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>

class DrawStrategy {
public:
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position, float size) = 0;
	virtual void update(void) = 0;
};

class SpriteDrawStrategy: public DrawStrategy {

	std::vector<sf::Sprite *> &sprites;
	unsigned int current_sprite_index;
	sf::Clock clock;
	unsigned int sprite_change_ms;

public:
	SpriteDrawStrategy(std::vector<sf::Sprite *> &sprites, unsigned int current_sprite_index): sprites(sprites) {
		this->current_sprite_index = current_sprite_index;
		this->sprite_change_ms = 500 + rand() % 1000;
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		sf::Sprite* current_sprite = this->sprites[current_sprite_index];

		current_sprite->setPosition(position);
		current_sprite->setScale({ size, size });
		window.draw(*(current_sprite));
	};

	void update() {
		if (this->clock.getElapsedTime().asMilliseconds() >= this->sprite_change_ms) {
			current_sprite_index = rand() % 7;
			this->clock.restart();
		}
	};
};


class TextDrawStrategy : public DrawStrategy {

	sf::Color colors[7] = {
		sf::Color::White,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Cyan
	};

	sf::Text* txt = nullptr;
	std::string content;
	sf::Color color;

	unsigned int character_change_ms;
	sf::Clock character_change_clock;
	unsigned int color_change_ms;
	sf::Clock color_change_clock;

	char get_random_character() {
		return 'a' + rand() % 26;
	};

public:

	TextDrawStrategy(sf::Text* text, std::string content) {
		this->txt = text;
		this->content = content;
		this->character_change_ms = rand() % 1500;
		this->color_change_ms = 500 + rand() % 1000;
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		this->txt->setPosition(position);
		this->txt->setCharacterSize(size * 20);
		this->txt->setFillColor(this->color);
		this->txt->setOutlineColor(sf::Color::White);
		this->txt->setOutlineThickness(0.5f);
		this->txt->setString(this->content);
		window.draw(*(this->txt));
	}

	void update() override {
		if (this->character_change_clock.getElapsedTime().asMilliseconds() >= this->character_change_ms) {
			this->content[rand() % content.length()] = this->get_random_character();
			this->character_change_clock.restart();
		}
		if (this->color_change_clock.getElapsedTime().asMilliseconds() >= this->color_change_ms) {
			this->color = this->colors[rand() % 7];
			this->color_change_clock.restart();
		}
	};
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
	sf::Clock clock;
	unsigned int update_ms = 0;

public:
	DotDrawStrategy(sf::CircleShape* circle): update_ms(500 + rand() % 1000) {
		this->dot = circle;
		this->color = this->colors[rand() % 7];
	};

	void draw(sf::RenderWindow& window, sf::Vector2f position, float size) override {
		this->dot->setPosition(position);
		this->dot->setRadius(size * 10);
		this->dot->setFillColor(this->color);

		window.draw(*(this->dot));
	}
	
	void update() override {
		if (this->clock.getElapsedTime().asMilliseconds() >= this->update_ms) {
			this->color = this->colors[rand() % 7];
			this->clock.restart();
		}
	}
};

#endif