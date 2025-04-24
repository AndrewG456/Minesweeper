#pragma once
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include "button.h"
#include "Random.h"

using namespace std;

struct Board_Loader
{
	static void random_Board(vector<vector<int>>& input, int rows, int columns, int num_Mines) {
		int j = 0;
		std::vector<bool> used(rows * columns + 1);
		input = vector<vector<int>>(rows, vector<int>(columns));
		for (int i = 0; i < num_Mines; i++) {
			j = Random::Int(0, rows * columns - 1);
			if (used[j] == 0) {
				input[floor(j / columns)][j % columns] = 1;
				used[j] = 1;
			}
			else {
				i--;
			}
		}
	}

	static void read_Config(std::string& filename, std::array<int, 3>& input) {
		std::ifstream file(filename);
		std::string buffer;
		int i = 0;
		while (std::getline(file, buffer)) {
			input[i] = stoi(buffer);
			i++;
		}
	}

	static void read_Board(std::string filename, std::vector<std::vector<int>>& input, int rows, int columns) {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Could not open " << filename << std::endl;
		}
		std::string buffer;
		int i = 0;
		input = vector<vector<int>>(columns , vector<int>(rows));
		while (std::getline(file, buffer)) {
			for (int j = 0; j < buffer.size(); j++) {
				input[j][i] = (buffer[j] - '0');
			}
			i++;
		}
	}
};
