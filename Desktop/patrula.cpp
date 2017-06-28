/* Copyright 2017 Pa */

#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>

class Graph {
	public:
		std::vector<std::vector<std::pair<int, int> > > adjList;
		int numberOfNodes;

		explicit Graph(int n) {
			numberOfNodes = n;
			adjList.resize(n);
		}

		void addEdge(int index1, int index2) {
			bool found = false;
			for (int i = 0; i < adjList[index1].size(); ++i) {
				if (adjList[index1][i].first == index2) {
					adjList[index1][i].second++;
					found = true;
				}
			}
			if (!found) {
				adjList[index1].push_back(std::pair<int, int>(index2, 1));
			}
		}
};

unsigned long long BFS(int start,
						int stop,
						Graph g,
						unsigned long long *nbOfEntries) {
	unsigned long long viz[g.numberOfNodes] = {0};
	unsigned long long d[g.numberOfNodes] = {0};

	viz[start] = 1;
	d[start] = 0;
	nbOfEntries[start] = 1;

	std::queue<int> coada;

	coada.push(start);

	while(!coada.empty()) {
		int current = coada.front();
		coada.pop();

		if (current == stop) {
			break;
		}

		for (std::vector<std::pair<int, int> >::iterator
												it = g.adjList[current].begin();
			 									it != g.adjList[current].end();
			 									++it) {
			if (viz[it->first] == 1) {
				if (d[it->first] == d[current] + 1) {
					nbOfEntries[it->first] += nbOfEntries[current] * it->second;
				}
			} else {
				d[it->first] = d[current] + 1;
				nbOfEntries[it->first] = nbOfEntries[current] * it->second;
				viz[it->first] = 1;
				coada.push(it->first);
			}
		}
	}

	return nbOfEntries[stop];
}

int main() {
	FILE *input = fopen("patrula.in", "r");
	FILE *output = fopen("patrula.out", "w");

	int N, M;
	assert(fscanf(input, "%d%d", &N, &M) == 2);

	Graph g(N);

	for (int i = 0; i < M; ++i) {
		int nod1, nod2;
		assert(fscanf(input, "%d%d", &nod1, &nod2) == 2);
		g.addEdge(nod1 - 1, nod2 - 1);
		g.addEdge(nod2 - 1, nod1 - 1);
	}

	unsigned long long nbOfPaths, ceva;
	unsigned long long nbOfEntFromStart[N] = {0};
	unsigned long long nbOfEntFromStop[N] = {0};


	nbOfPaths = BFS(N - 1, 0, g, nbOfEntFromStart);
	BFS(0, N - 1, g, nbOfEntFromStop);

	double max = nbOfPaths;

	for (int i = 1; i < N - 1; ++i) {
		unsigned long long nb = nbOfEntFromStart[i] * nbOfEntFromStop[i] * 2;
		if (max < nb) {
			max = nb;
		}
	}

	fprintf(output, "%llu\n", nbOfPaths);

	double average = max / nbOfPaths;
	fprintf(output, "%.3f", average);

	fclose(input);
	fclose(output);
}
