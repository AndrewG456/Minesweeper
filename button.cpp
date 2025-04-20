#include "button.h"
#include <iostream>
button::button(int* pos, int* size, sf::Texture& basic, std::string type, sf::Texture& pressed) {
	this->location.push_back(pos[0]);
	this->location.push_back(pos[0] + size[0]);
	this->location.push_back(pos[1]);
	this->location.push_back(pos[1] + size[1]);
	this->basic = basic;
	this->pressed = pressed;
	this->sprite.setTexture(this->basic, true);
	this->sprite.setTextureRect(sf::IntRect(0, 0, size[0], size[1]));
	this->type = type;
	sprite.setPosition({ (float)this->location[0], (float)this->location[2] });
}
