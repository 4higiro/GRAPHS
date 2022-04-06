// Including
#include <iostream>
#include <fstream>
#include "graph.h"

// Using names
using namespace std;

// Enterence to program
void main()
{
	// Set localisation
	setlocale(LC_ALL, "Ru");

	// Reading input data
	ifstream file;

	file.open("data.txt");

	if (!file.is_open())
	{
		cout << "FILE NOT OPEN" << endl;
		return;
	}

	int n;
	file >> n;

	int** matrix = new int* [n];

	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];

		for (int j = 0; j < n; j++)
		{
			file >> matrix[i][j];
		}
	}

	file.close();

	cout << "Input matrix:" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << "  ";
		}

		cout << endl;
	}

	// Create graph
	graph g;
	g.init(matrix, n);

	// Dijkstra algorithm
	int result;
	int* path = new int[n];

	g.dijkstra(result, path, 2, 4);

	cout << endl << "Dijkstra(" << result << "):" << "\t";

	for (int i = 0; i < n; i++)
	{
		cout << path[i] << "\t";
	}

	cout << endl;

	// Prim-Craskal algorithm
	int** frame = new int* [n];

	for (int i = 0; i < n; i++)
	{
		frame[i] = new int[n];
	}

	g.primCraskal(frame);

	cout << endl << "Frame's matrix:" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << frame[i][j] << "  ";
		}

		cout << endl;
	}

	cout << endl;

	g.floyd(result, 2, 4);

	cout << endl << "Floyd (" << result << ")" << "\t";

	cout << endl;

	system("pause");
}