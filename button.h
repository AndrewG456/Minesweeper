#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
struct button {
	button(){};
	button(int* pos, int* size, sf::Texture& basic, std::string type, sf::Texture& pressed);
	std::vector<int> location;
	sf::Texture basic;
	sf::Sprite sprite;
	std::string type;
	sf::Texture pressed;
	bool locked = 0;
	bool flagged = 0;
	bool edge = 0;
	bool debug_vis = false;
	int adj_mines = 0;

};