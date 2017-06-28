/* Copyright 2017 Pa */

#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <algorithm>

#define nbOfLetters 26

void dfs(int start,
		 int matrix[nbOfLetters][nbOfLetters],
		 int viz[nbOfLetters],
		 std::stack<char> &result,
		 bool &cycleDetected) {
	viz[start] = -1;

	for (int i = 0; i < nbOfLetters; i++) {
		std::cout << viz[i] << " ";
	}

	for (int i = 0; i < nbOfLetters; ++i) {
		if (matrix[start][i] == 1) {
			if (viz[i] == -1) {
					cycleDetected = true;
					return;
			}
			if (viz[i] == 0) {
				dfs(i, matrix, viz, result, cycleDetected);
			}
		}
	}
	viz[start] = 1;
	result.push(start + 'a');
}

bool topologicalSort(int matrix[nbOfLetters][nbOfLetters],
					 int viz[nbOfLetters],
					 std::stack<char> &result) {
		for (int i = 0; i < nbOfLetters; ++i) {
			if (!viz[i]) {
				bool cycleDetected = false;
				dfs(i, matrix, viz, result, cycleDetected);
				if (cycleDetected) {
					return true;
				}
			}
		}

	return false;
}

bool readFromFile(int matrix[nbOfLetters][nbOfLetters]) {
	FILE *input = fopen("permutari.in", "r");

	int nbOfWords;
	assert(fscanf(input, "%d", &nbOfWords) == 1);

	char currentWord[100];
	assert(fscanf(input, "%s", currentWord) == 1);

	for (int i = 1; i < nbOfWords; ++i) {
		char newWord[100];
		assert(fscanf(input, "%s", newWord) == 1);

		int lenCurr = strlen(currentWord);
		int lenNew = strlen(newWord);

		bool error = true;
		for (int i = 0; i < std::min(lenNew, lenCurr); ++i) {
			if (currentWord[i] != newWord[i]) {
				std::cout << "ups " << currentWord[i] << " " << newWord[i] << "\n";
				matrix[currentWord[i] - 'a'][newWord[i] - 'a'] = 1;
				error = false;
				break;
			}
		}

		if (error && lenCurr > lenNew) {
			return error;
		}

		strcpy(currentWord, newWord);
	}

	fclose(input);
	return false;
}

int main() {
	FILE *output = fopen("permutari.out", "w");

	int matrix[nbOfLetters][nbOfLetters] = {0};
	int viz[nbOfLetters] = {0};
	std::stack<char> result;

	if (readFromFile(matrix) || topologicalSort(matrix, viz, result)) {
		char error[10] = "Imposibil";
		fprintf(output, "%s", error);
	} else {
		while (!result.empty()) {
			fprintf(output, "%c", result.top());
			result.pop();
		}
	}

	fclose(output);
}
