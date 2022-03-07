// Including
#include <iostream>
#include "graph.h"

// Using names
using namespace std;

// Default constructor
graph::graph()
{
	matrix = nullptr;
	n = 0;
}

// Graph initialization
void graph::init(int** matrix, int n)
{
	this->n = n;

	this->matrix = new int* [n];

	for (int i = 0; i < n; i++)
	{
		this->matrix[i] = new int[n];

		for (int j = 0; j < n; j++)
		{
			this->matrix[i][j] = matrix[i][j];
		}
	}
}

// Freeing memory
void graph::clear()
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;

	n = 0;
}

// Search of min paths
void graph::dijkstra(int& result, int* path, int start, int finish)
{
	int* a = new int[n]; // Array of traversed graph vertices
	int* b = new int[n]; // Array of min paths
	int* c = new int[n]; // Array of traversed path

	// Start value
	for (int i = 0; i < n; i++) {
		a[i] = 0;
		b[i] = matrix[start][i];
		c[i] = -1;
	}

	int current = -1;

	// Algorithm's main loop
	for (int i = 0; i < n; i++) {
		// Search of min weight
		int minIndex;
		for (int j = 0; j < n; j++) {
			if (a[j] == 0) {
				minIndex = j;
				break;
			}
		}
		for (int j = 0; j < n; j++) {
			if (a[j] == 0 && b[minIndex] > b[j])
				minIndex = j;
		}
		a[minIndex] = 1;
		c[minIndex] = current;
		// Update arrays
		for (int j = 0; j < n; j++) {
			if (a[j] == 0)
				b[j] = min(b[j], b[minIndex] + matrix[minIndex][j]);
		}
		current = minIndex;
	}

	// Writing result
	result = b[finish];

	path[0] = start;

	for (int i = 1; i < n; i++)
	{
		int index = 0;
		for (int j = 0; j < n; j++)
		{
			if (c[j] == path[i - 1])
			{
				index = j;
			}
		}
		path[i] = index;
	}
}

// Search of min spanning tree
void graph::primCraskal(int** frame)
{
	// Array of colors
	int* colors = new int[n];
	for (int i = 0; i < n; i++)
		colors[i] = i;

	// Arrays of frame's edges
	int** edges = new int* [2];
	edges[0] = new int[n - 1];
	edges[1] = new int[n - 1];

	// Algorithm's main loop
	for (int i = 0; i < n - 1; i++) {
		// Search of min edge
		int minX = 0;
		int minY = 1;
		for (int j = 0; j < n; j++) {
			if (colors[minX] == colors[minY]) {
				minY++;
			}
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (matrix[minX][minY] > matrix[j][k] && j != k && colors[j] != colors[k]) {
					minX = j;
					minY = k;
				}
			}
		}
		// Writing edge
		edges[0][i] = minX;
		edges[1][i] = minY;
		// Update colors
		for (int j = 0; j < n; j++) {
			if (j == minX || j == minY) {
				int current = colors[j];
				for (int k = 0; k < n; k++) {
					if (colors[k] == current)
						colors[k] = minX;
				}
			}
		}
	}

	// Writing result
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			frame[i][j] = matrix[i][j];
		}
		for (int j = i; j < n; j++) {
			bool f = true;
			for (int k = 0; k < n - 1; k++) {
				if (i == edges[0][k] && j == edges[1][k])
					f = false;
			}
			if (f) {
				frame[i][j] = 99999;
				frame[j][i] = 99999;
			}
		}
		frame[i][i] = 0;
	}

}
