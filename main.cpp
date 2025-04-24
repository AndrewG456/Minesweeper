#include "button.h"
#include "Random.h"
#include "Board_Loader.h"
#include <vector>
#include <iostream>
#include <array>
#include <cmath>
#include <fstream>
#include <algorithm>
using std::vector;

bool check_Win(vector<vector<button>>& board) {
    for (vector<button>& row : board) {
        for (button& b : row) {
            if (b.locked == 0 && b.adj_mines != 9) {
                return false;
                break;
            }
        }
    }
    return true;
}

void flag_Mines(vector<vector<button>>& board, array<sf::Texture, 31>& textures) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j].locked == 0 && board[i][j].adj_mines == 9) {
                board[i][j].sprite.setTexture(textures[1]);
            }
        }
    }
}

void reveal_Mines(vector<vector<button>>& board, array<sf::Texture, 31>& textures) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j].locked == 0 && board[i][j].adj_mines == 9) {
                board[i][j].sprite.setTexture(textures[11]);
            }
        }
    }
}

void loss(vector<vector<button>>& board, std::array<button, 5>& buttons, std::array<sf::Texture, 31>& textures) {
    buttons[0].sprite.setTexture(textures[17]);
    reveal_Mines(board, textures);
}

void win(vector<vector<button>>& board, std::array<button, 5>& buttons, std::array<sf::Texture, 31>& textures) {
    buttons[0].sprite.setTexture(textures[18]);
    flag_Mines(board, textures);
}

void left_Click_Grid(button& b, vector<vector<int>>& mines, vector<vector<button>>& board, int row, int column) {
    if (b.flagged == false) {
        b.sprite.setTexture(b.pressed); // Preloaded texture
        b.locked = 1;
        if (b.adj_mines == 0) {
            for (int k = 0; k < 3; k++) {
                for (int p = 0; p < 3; p++) {
                    if ((row + k - 1) >= 0 && (column + p - 1) >= 0 && (row + k - 1) < mines.size() && (column + p - 1) < mines[0].size() && board[row + k - 1][column + p - 1].locked == 0) {
                        left_Click_Grid(board[row + k - 1][column + p - 1], mines, board, row + k - 1, column + p - 1);
                    }
                }
            }
        }
    }

}

void right_Click_Grid(button& b, std::array<sf::Texture, 31>& textures, int& num_Flagged) {
    if (b.locked == 0 && b.flagged == 0) {
        b.sprite.setTexture(textures[1]); // Preloaded flag texture
        b.flagged = 1;
        num_Flagged++;
    }
    else if (b.locked == 0 && b.flagged == 1) {
        b.sprite.setTexture(textures[0]);
        b.flagged = 0;
        num_Flagged--;
    }
}

void test_mines(vector<vector<button>>& buttons, vector<vector<int>>& mines, array<sf::Texture, 31>& textures) {
    for (int i = 0; i < buttons.size(); i++) {
        for (int j = 0; j < buttons[0].size(); j++) {
            if (mines[i][j] == 1 && buttons[i][j].debug_vis == 0 && buttons[i][j].locked == 0) {
                buttons[i][j].sprite.setTexture(buttons[i][j].pressed); // Preloaded texture
                buttons[i][j].debug_vis = 1;
            }
            else if (buttons[i][j].locked == 0 && mines[i][j] == 1 && buttons[i][j].flagged == false) {
                buttons[i][j].sprite.setTexture(buttons[i][j].basic); // Preloaded texture
                buttons[i][j].debug_vis = 0;
            }
            else if (buttons[i][j].locked == 0 && mines[i][j] == 1 && buttons[i][j].flagged == true) {
                buttons[i][j].sprite.setTexture(textures[1]); // Preloaded texture
                buttons[i][j].debug_vis = 0;
            }
        }
    }

}

void load_textures(std::array<sf::Texture, 31>& textures) {
    if (!textures[1].loadFromFile("images/flag.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[0].loadFromFile("images/tile_hidden.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[2].loadFromFile("images/tile_revealed.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    if (!textures[30].loadFromFile("images/tile_hidden.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    for (int i = 1; i < 9; i++) {
        if (!textures[2 + i].loadFromFile("images/number_" + std::to_string(i) + ".png", sf::IntRect(0, 0, 32, 32))) {
            std::cerr << "Failed to load texture!" << std::endl;
        }
    }
    if (!textures[11].loadFromFile("images/mine.png", sf::IntRect(0, 0, 32, 32))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[12].loadFromFile("images/face_happy.png", sf::IntRect(0, 0, 64, 64))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[13].loadFromFile("images/debug.png", sf::IntRect(0, 0, 64, 64))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    for (int i = 1; i < 4; i++) {
        if (!textures[13 + i].loadFromFile("images/test_" + std::to_string(i) + ".png", sf::IntRect(0, 0, 64, 64))) {
            std::cerr << "Failed to load texture!" << std::endl;
        }
    }
    if (!textures[17].loadFromFile("images/face_lose.png", sf::IntRect(0, 0, 64, 64))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!textures[18].loadFromFile("images/face_win.png", sf::IntRect(0, 0, 64, 64))) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    for (int i = 0; i < 11; i++) {
        if (!textures[19 + i].loadFromFile("images/digits.png", sf::IntRect(21 * i, 0, 21, 32))) {
            std::cerr << "Failed to load texture!" << std::endl;
        }
    }

}

void initialize_bottom_row(std::array<button, 5>& bottom_buttons, std::array<sf::Texture, 31>& textures, int rows, int columns) {
    int pos[2] = { rows * 16, 32 * columns };
    int size[2] = { 64, 64 };
    bottom_buttons[0] = button(pos, size, textures[12], "smiley", textures[12]);
    bottom_buttons[0].sprite.setTexture(textures[12]);
    pos[0] += 128;
    for (int i = 1; i < 5; i++) {
        bottom_buttons[i] = button(pos, size, textures[12 + i], "test" + std::to_string(i + 1), textures[12 + i]);
        bottom_buttons[i].sprite.setTexture(textures[12 + i]);
        pos[0] += 64;
    }
    bottom_buttons[1].sprite.setTexture(textures[13]);
}

void initialize_grid(vector<vector<button>>& grid_buttons, vector<vector<int>>& mines, std::array<sf::Texture, 31>& textures, int num_mines) {
    int pos[2];
    int count = 0;
    int size[2] = { 32, 32 };
    std::string type = "clean";
    Board_Loader::random_Board(mines, grid_buttons.size(), grid_buttons[0].size(), num_mines);
    for (int i = 0; i < grid_buttons.size(); i++) {
        pos[0] = i * 32;
        for (int j = 0; j < mines[0].size(); j++) {
            pos[1] = j * 32;
            if (mines[i][j] == 1) {
                type = "mine";
                grid_buttons[i][j] = button(pos, size, textures[0], type, textures[11]);
                grid_buttons[i][j].edge = false;
                grid_buttons[i][j].adj_mines = 9;
            }
            else {
                type = "clean";

                for (int k = 0; k < 3; k++) {
                    for (int y = 0; y < 3; y++) {
                        if ((i + k - 1) >= 0 && (j + y - 1) >= 0 && (i + k - 1) < mines.size() && (j + y - 1) < mines[0].size()) {
                            if (mines[i + k - 1][j + y - 1] == 1) {
                                count++;
                            }
                        }
                    }
                }

                if (count == 0) {
                    grid_buttons[i][j] = button(pos, size, textures[0], type, textures[2]);
                }
                else {
                    grid_buttons[i][j] = button(pos, size, textures[0], type, textures[2 + count]);
                    grid_buttons[i][j].adj_mines = count;
                }
            }
            grid_buttons[i][j].sprite.setTexture(textures[0]);
            count = 0;
        }
    }
}

void live_Initialize(vector<vector<button>>& grid_buttons, vector<vector<int>>& mines, std::array<sf::Texture, 31>& textures) {
    int pos[2];
    int count = 0;
    int size[2] = { 32, 32 };
    grid_buttons = vector<vector<button>>(mines.size(), vector<button>(mines[0].size()));
    std::string type = "clean";
    for (int i = 0; i < grid_buttons.size(); i++) {
        pos[0] = i * 32;
        for (int j = 0; j < mines[0].size(); j++) {
            pos[1] = j * 32;
            if (mines[i][j] == 1) {
                type = "mine";
                grid_buttons[i][j] = button(pos, size, textures[0], type, textures[11]);
                grid_buttons[i][j].edge = false;
                grid_buttons[i][j].adj_mines = 9;
            }
            else {
                type = "clean";

                for (int k = 0; k < 3; k++) {
                    for (int y = 0; y < 3; y++) {
                        if ((i + k - 1) >= 0 && (j + y - 1) >= 0 && (i + k - 1) < mines.size() && (j + y - 1) < mines[0].size()) {
                            if (mines[i + k - 1][j + y - 1] == 1) {
                                count++;
                            }
                        }
                    }
                }

                if (count == 0) {
                    grid_buttons[i][j] = button(pos, size, textures[0], type, textures[2]);
                }
                else {
                    grid_buttons[i][j] = button(pos, size, textures[0], type, textures[2 + count]);
                    grid_buttons[i][j].adj_mines = count;
                }
            }
            grid_buttons[i][j].sprite.setTexture(textures[0]);
            count = 0;
        }
    }
}

void initialize_counter(vector<vector<button>>& counter, std::array<sf::Texture, 31>& textures, int rows) {
    counter = vector<vector<button>>(4, vector<button>(11));
    int pos[2], size[2];
    pos[1] = rows * 32;
    pos[0] = 0;
    size[0] = 21;
    size[1] = 32;
    for (int i = 0; i < counter.size(); i++) {
        for (int j = 0; j < counter[0].size(); j++) {
            counter[i][j] = button(pos, size, textures[19 + j], "counter", textures[19 + j]);
            counter[i][j].sprite.setTexture(textures[19 + j]);
        }
        pos[0] += 21;
    }

}

int main() {
    bool game_Over = false, game_state = false;
    int num_Flags = 0;
    std::array<int, 3> configuration;
    std::string filename = "boards/config.cfg";
    std::string boardfile;
    Board_Loader::read_Config(filename, configuration);
    vector<vector<int>> mines;
    int columns = configuration[0], rows = configuration[1], num_Mines = configuration[2];
    sf::RenderWindow window(sf::VideoMode(columns * 32, rows * 32 + 100), "Andrew George - Minesweeper");
    sf::View view(sf::FloatRect(0, 0, columns * 32, rows * 32 + 100));
    std::array<sf::Texture, 31> textures;
    sf::Texture bkg;
    load_textures(textures);
    vector<vector<button>> counter;
    textures[30].setRepeated(true);
    sf::Texture a;
    sf::Sprite sprit(a);
    sprit.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sf::Sprite sprite(textures[30]);
    sprite.setTextureRect(sf::IntRect(0, 0, columns * 32, rows * 32));
    vector<vector<button>> grid_buttons(columns, vector<button>(rows));
    std::array<button, 5> bottom_buttons;
    initialize_grid(grid_buttons, mines, textures, configuration[2]);
    initialize_bottom_row(bottom_buttons, textures, columns, rows);
    initialize_counter(counter, textures, rows);
    sf::RectangleShape rec(sf::Vector2f(columns, rows * 32 + 100));
    rec.setFillColor(sf::Color(90, 90, 90));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i local_Pos = sf::Mouse::getPosition(window);
                if (game_Over == false) {
                    for (int i = 0; i < grid_buttons.size(); i++) {
                        if (local_Pos.x > grid_buttons[i][0].location[0] && local_Pos.x < grid_buttons[i][0].location[1]) {
                            for (int j = 0; j < grid_buttons[0].size(); j++) {
                                if (local_Pos.y > grid_buttons[i][j].location[2] && local_Pos.y < grid_buttons[i][j].location[3]) {
                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                        left_Click_Grid(grid_buttons[i][j], mines, grid_buttons, i, j);
                                        game_Over = check_Win(grid_buttons);
                                        game_state = game_Over;
                                        if (grid_buttons[i][j].adj_mines == 9) {
                                            game_Over = true;
                                        }
                                    }
                                    else {
                                        right_Click_Grid(grid_buttons[i][j], textures, num_Flags);
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                for (int i = 0; i < bottom_buttons.size(); i++) {
                    if (local_Pos.x > bottom_buttons[i].location[0] && local_Pos.x < bottom_buttons[i].location[1] && local_Pos.y > bottom_buttons[i].location[2] && local_Pos.y < bottom_buttons[i].location[3]) {
                        if (i == 0) {
                            initialize_grid(grid_buttons, mines, textures, configuration[2]);
                            initialize_bottom_row(bottom_buttons, textures, mines.size(), mines[0].size());
                            game_Over = false;
                            num_Flags = 0;
                            num_Mines = 0;
                            for (vector<int>& row : mines) {
                                num_Mines += count(row.begin(), row.end(), 1);
                            }
                        }
                        if (i == 1) {
                            test_mines(grid_buttons, mines, textures);
                        }
                        if (i > 1) {
                            boardfile = "boards/testboard" + std::to_string(i - 1) + ".brd";
                            Board_Loader::read_Board(boardfile, mines, rows, columns);
                            for (int l = 0; l < mines.size(); l++) {
                                for (int f = 0; f < mines[0].size(); f++) {
                                }
                            }
                            live_Initialize(grid_buttons, mines, textures);
                            initialize_bottom_row(bottom_buttons, textures, mines.size(), mines[0].size());
                            sprite.setTextureRect(sf::IntRect(0, 0, mines.size() * 32, mines[0].size() * 32));
                            game_Over = false;
                            num_Mines = 0;
                            num_Flags = 0;
                            for (vector<int>& row : mines) {
                                num_Mines += count(row.begin(), row.end(), 1);
                            }

                        }
                    }
                }
            }

            if (event.type == sf::Event::Resized) {
                float newWidth = event.size.width;
                float newHeight = event.size.height;
                view.setSize(newWidth, newHeight);
                view.setCenter(newWidth / 2, newHeight / 2);

                window.setView(view);

            }
        }
        if (game_Over == true) {
            if (game_state) {
                win(grid_buttons, bottom_buttons, textures);
            }
            else {
                loss(grid_buttons, bottom_buttons, textures);
            }
        }
        window.clear();
        window.draw(sprite);
        for (int i = 0; i < grid_buttons.size(); i++) {
            for (int j = 0; j < grid_buttons[0].size(); j++) {
                window.draw(grid_buttons[i][j].sprite);
            }
            for (int i = 4; i >= 0; i--) {
                window.draw(bottom_buttons[i].sprite);
            }
        }
        if (num_Mines - num_Flags < 0) {
            window.draw(counter[0][10].sprite);
        }

        window.draw(counter[1][abs(static_cast<int>(abs(num_Mines - num_Flags) / 100))].sprite);
        window.draw(counter[2][abs(static_cast<int>(abs(num_Mines - num_Flags) / 10 - 10 * (int)((abs(num_Mines - num_Flags)) / 100)))].sprite);
        window.draw(counter[3][abs(static_cast<int>(abs(num_Mines - num_Flags) - 10 * (int)(abs(num_Mines - num_Flags) / 10)))].sprite);

        window.draw(bottom_buttons[1].sprite);
        window.display();
    }


    return 0;
}
