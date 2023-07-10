#ifndef GAME_HPP
#define GAME_HPP

// #include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include "Particle.hpp"
#include "Button.hpp"

class Game {
	unsigned int width;
	unsigned int height;
	sf::RenderWindow window;

	std::vector<Particle*> particles;

	Button button;

	sf::Font font;
	sf::Text text;

	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite*> sprites;
	
	sf::CircleShape dot;

	void loadResources() {
		std::filesystem::path font_path;

		font_path = "assets";
		font_path /= "fonts";
		font_path /= "tuffy.ttf";
		std::ifstream file(font_path.c_str());
		if (!file.good()) std::cerr << "Couldn't open or read '" << font_path << "'" << std::endl;

		this->font.loadFromFile(font_path.string());
		this->text.setFont(this->font);
		// this->button = Button({ 550, 290 }, { 50, 20 }, "Ok", this->font);

		std::vector<std::string> paths = {
			"computer_explorer_2k-3.png", "executable-0.png", "game_freecell-1.png",
			"game_solitaire-0.png", "help_book_big-0.png", "ms_dos-1.png",
			"msie1-1.png", "processor-1.png", "recycle_bin_full-0.png",
			"windows-0.png", "wm-2.png"
		};

		for (const auto& path : paths) {
			std::filesystem::path final_path;

			final_path = "assets";
			final_path /= "images";
			final_path /= path;

			std::ifstream file(final_path.c_str());
			if (!file.good()) {
				std::cerr << "Couldn't open or read '" << final_path << "'" << std::endl;
				continue;
			}

			sf::Texture* current_texture = new sf::Texture();
			if (!current_texture->loadFromFile(final_path.string())) {
				std::cerr << "Couldn't load '" << final_path << "'" << std::endl;
				delete current_texture;
				continue;
			}

			sf::Sprite* current_sprite = new sf::Sprite();
			current_sprite->setTexture(*current_texture);
			this->textures.push_back(current_texture);
			this->sprites.push_back(current_sprite);
		}
	}

public:
	Game(unsigned int width, unsigned int height) :
		width(width),
		height(height),
		window(sf::VideoMode(this->width, this->height), "Particle system")
	{
		srand(time(NULL));
		this->loadResources();

		for (unsigned int i = 0; i < 60; ++i) {
			Particle* current_particle = new Particle(
				{ (float)(rand() % this->width), (float)(rand() % this->height) },
				1 + (float)rand() / (float)(RAND_MAX),
				{static_cast<float>(rand() % 101) / 100.0f * 100.0f - 50.0f, static_cast<float>(rand() % 101) / 100.0f * 100.0f - 50.0f }
			);
			switch (rand() % 3) {
			case 0:
				current_particle->setDrawStrategy(new SpriteDrawStrategy(this->sprites, rand() % this->sprites.size()));
				break;
			case 1:
				current_particle->setDrawStrategy(new TextDrawStrategy(&this->text, "ABCD"));
				break;
			case 2:
				current_particle->setDrawStrategy(new DotDrawStrategy(&this->dot));
				break;
			};
			particles.push_back(current_particle);
		}
	};

	void pollEvents() {
		sf::Event event;

		while (this->window.pollEvent(event)) {
			switch (event.type) {
			case (sf::Event::Closed):
				this->window.close();
				break;
			case (sf::Event::MouseButtonPressed):
				const sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
				const sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
				std::cout << "Mouse was clicked at " << mousePos.x << " " << mousePos.y << std::endl;
				if (this->button.isInBounds(mousePosFloat)) {
					this->button.execute();
				}
				break;
			}
		}
	};

	void update()
	{
		sf::FloatRect screenBoundaries({ 0, 0 }, sf::Vector2f({ (float)(this->width), (float)(this->height) }));
		for (auto& it : this->particles) {
			if (screenBoundaries.contains(it->getPosition()) == false) {
				it->setPosition({ (float)(this->width) / 2, (float)(this->height) / 2 });
				switch (rand() % 3) {
				case 0:
					it->setDrawStrategy(new SpriteDrawStrategy(this->sprites, rand() % this->sprites.size()));
					break;
				case 1:
					it->setDrawStrategy(new TextDrawStrategy(&this->text, "ABCD"));
					break;
				case 2:
					it->setDrawStrategy(new DotDrawStrategy(&this->dot));
					break;
				};
			}
			it->update();
		}
	}

	void draw()
	{
		for (auto &it: this->particles)
			it->draw(this->window);
		this->button.draw(this->window);
		this->window.display();
	}

	void run()
	{
		while (this->window.isOpen()) {
			this->window.clear(sf::Color::Black);
			this->pollEvents();
			this->update();
			this->draw();
		}
	}

	~Game() {
		for (auto texture : this->textures)
			delete texture;
		for (auto sprite : this->sprites)
			delete sprite;
		for (auto particle : this->particles)
			delete particle;
	}
};

#endif