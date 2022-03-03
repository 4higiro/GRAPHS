// Including
#include <iostream>
#include <fstream>

// Using names
using namespace std;

// ����� �����
class graph
{
private:
	int** matrix;
	int n;
public:
	// ����������� �� ���������
	graph()
	{
		matrix = nullptr;
		n = 0;
	}

	// ������������� �����
	void init(int** matrix, int n)
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

	// ������� ������
	void clear()
	{
		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}

		delete[] matrix;

		n = 0;
	}

	void dijkstra(int& result, int n1, int n2) {
		int* a = new int[n]; // ������ � ��������� ���������� ������
		int* b = new int[n]; // ������ � ����������� ������������

		// ��������� �������� ��������
		for (int i = 0; i < n; i++) {
			a[i] = 0;
			b[i] = matrix[n1][i];
		}

		// �������� ���� ���������
		for (int i = 0; i < n; i++) {
			int minIndex; // ����� ������������ �����
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
			// ���������� ���������� ����������
			for (int j = 0; j < n; j++) {
				if (a[j] == 0)
					b[j] = min(b[j], b[minIndex] + matrix[minIndex][j]);
			}
		}

		// ������ ����������
		result = b[n2];
	}

	// �������� �����-��������
	void primCraskal(int& result) {
		// ������ ��������� ������
		int* colors = new int[n];
		for (int i = 0; i < n; i++)
			colors[i] = i;

		// ������ �����, ������������� ������������ ��������� ������
		int** edges = new int* [2];
		edges[0] = new int[n - 1];
		edges[1] = new int[n - 1];

		result = 0;

		// �������� ���� ���������
		for (int i = 0; i < n - 1; i++) {
			// ����� ������������ �����
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
			// ������ �����
			edges[0][i] = minX;
			edges[1][i] = minY;
			// �������������� ������
			for (int j = 0; j < n; j++) {
				if (j == minX || j == minY) {
					int current = colors[j];
					for (int k = 0; k < n; k++) {
						if (colors[k] == current)
							colors[k] = minX;
					}
				}
			}
			// ������� ����� �������� ����� ������
			result += matrix[minX][minY];
		}
	}
};


// Enterence to program
void main()
{
	// Set localisation
	setlocale(LC_ALL, "Ru");

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

	graph g;
	g.init(matrix, n);

	int result;
	g.dijkstra(result, 2, 4);

	cout << result << endl;

	g.primCraskal(result);

	cout << result << endl;

}