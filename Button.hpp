#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
	sf::Vector2f position;
	sf::Vector2i dimensions;
	sf::RectangleShape appearance;
	sf::Text text;
	std::function<void(void)> behavior;


public:
	Button() = default;
	Button(sf::Vector2f position, sf::Vector2f dimensions, std::string content, sf::Font& font) :
		position(std::move(position)),
		dimensions(dimensions),
		appearance(std::move(dimensions)),
		text(std::move(content), font, 15),
		behavior([]() {std::cout << "default behavior" << std::endl; })
	{
		this->appearance.setPosition(position);
		this->appearance.setFillColor(sf::Color(100, 100, 100, 255));

		sf::FloatRect txt_bounds = this->text.getLocalBounds();
		this->text.setPosition(this->position.x + this->dimensions.x / 2 - txt_bounds.width / 2, this->position.y);
		this->text.setFillColor(sf::Color::White);
	};

	void draw(sf::RenderWindow& window) {
		window.draw(this->appearance);
		window.draw(this->text);
	};

	[[nodiscard]] bool isInBounds(sf::Vector2f position) const {
		return this->appearance.getGlobalBounds().contains(position);
	};

	void setBehavior(std::function<void(void)> fct) {
		this->behavior = fct;
	};

	void execute() {
		this->behavior();
	};
};

#endif