#include "button.h"
#include "Random.h"
#include <vector>
#include <iostream>
#include <array>
#include <cmath>
using std::vector;


void left_Click_Grid(button& b) {
    b.sprite.setTexture(b.pressed); // Preloaded texture
    b.locked = 1;
}

void right_Click_Grid(button& b, std::array<sf::Texture, 21>& textures) {
    if (b.locked == 0 && b.flagged == 0) {
        b.sprite.setTexture(textures[1]); // Preloaded flag texture
        b.flagged = 1;
    }
    else if (b.locked == 0 && b.flagged == 1) {
        b.sprite.setTexture(textures[0]);
        b.flagged = 0;
    }
}

void initialize(std::array<std::array<button, 11>, 25>& grid_buttons, std::array<sf::Texture, 21>& textures) {
    int pos[2];
    int count = 0;
    int size[2] = { 32, 32 };
    std::string type = "clean";
    std::array<std::array<int, 13>, 27> mine;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 11; j++) {
            mine[i + 1][j + 1] = Random::Int(0, 1);
        }
    }
    for (int i = 0; i < 25; i++) {
        pos[0] = i * 32;
        for (int j = 0; j < 11; j++) {
            pos[1] = j * 32;
            if (mine[i + 1][j + 1] == 1) {
                type = "mine";
                grid_buttons[i][j] = button(pos, size, textures[1], type, textures[11]);
            }
            else {
                type = "clean";
                    for (int k = 0; k < 3; k++) {
                        for (int p = 0; p < 3; p++) {
                        if (mine[i + k][j + p] == 1) {
                            count++;
                        }
                    }
                }

                if (count == 0) {
                    grid_buttons[i][j] = button(pos, size, textures[1], type, textures[2]);
                }
                else {
                    grid_buttons[i][j] = button(pos, size, textures[1], type, textures[2 + count]);
                }
            }
            grid_buttons[i][j].sprite.setTexture(textures[0]);
            count = 0;
            std::cout << i << ", " << j << std::endl;
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 448), "SFML works!");
    std::array<sf::Texture, 21> textures;
    if (!textures[1].loadFromFile("images\\flag.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    //sf::Texture texture("images/test_1.png", false, sf::IntRect({ 10, 10 }, { 32, 32 });
    if (!textures[0].loadFromFile("images\\tile_hidden.png", sf::IntRect(0, 0, 32, 32))) {
        //std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[2].loadFromFile("images\\tile_revealed.png", sf::IntRect(0, 0, 32, 32))) {
        //std::cerr << "Failed to load texture!" << std::endl;
    }

    if (!textures[20].loadFromFile("images\\tile_hidden.png", sf::IntRect(0, 0, 32, 32))) {
        //std::cerr << "Failed to load texture!" << std::endl;
    }
    for (int i = 1; i < 9; i++) {
        if (!textures[2+i].loadFromFile("images\\number_" + std::to_string(i) + ".png", sf::IntRect(0, 0, 32, 32))) {
            //std::cerr << "Failed to load texture!" << std::endl;
        }
    }
    if (!textures[11].loadFromFile("images\\mine.png", sf::IntRect(0, 0, 32, 32))) {
        //std::cerr << "Failed to load texture!" << std::endl;
    }
    textures[20].setRepeated(true);
    sf::Sprite sprite(textures[20]);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 352));
    std::array<std::array<button, 11>, 25> grid_buttons;
    initialize(grid_buttons, textures);
    //std::cout << grid_buttons.size();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // Correct event handling
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                std::cout << "started";
                sf::Vector2i local_Pos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 25; i++) {
                    std::cout << "two";
                    if (local_Pos.x > grid_buttons[i][0].location[0] && local_Pos.x < grid_buttons[i][0].location[1]) {
                        std::cout << "three";
                        for (int j = 0; j < 11; j++) {
                            if (local_Pos.y > grid_buttons[i][j].location[2] && local_Pos.y < grid_buttons[i][j].location[3]) {
                                std::cout << "four";
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                    left_Click_Grid(grid_buttons[i][j]);
                                }
                                else {
                                    std::cout << "five";
                                    right_Click_Grid(grid_buttons[i][j], textures);
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        std::cout << grid_buttons[0].size() << std::endl;
        std::cout << grid_buttons[0][0].location.size();
        window.clear();
        window.draw(sprite);
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 11; j++) {
                window.draw(grid_buttons[i][j].sprite);
            }
        }
        window.display();
    }

    return 0;
}
