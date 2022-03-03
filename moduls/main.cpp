// Including
#include <iostream>
#include <fstream>

// Using names
using namespace std;

// Класс графа
class graph
{
private:
	int** matrix;
	int n;
public:
	// Конструктор по умоляанию
	graph()
	{
		matrix = nullptr;
		n = 0;
	}

	// Инициализация графа
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

	// Очитска памяти
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
		int* a = new int[n]; // Массив с отметками пройденных вершин
		int* b = new int[n]; // Массив с кратчайшими расстояниями

		// Начальные значения массивов
		for (int i = 0; i < n; i++) {
			a[i] = 0;
			b[i] = matrix[n1][i];
		}

		// Основной цикл алгоритма
		for (int i = 0; i < n; i++) {
			int minIndex; // Поиск минимального ребра
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
			// Вычисление кратчайших расстояний
			for (int j = 0; j < n; j++) {
				if (a[j] == 0)
					b[j] = min(b[j], b[minIndex] + matrix[minIndex][j]);
			}
		}

		// Запись результата
		result = b[n2];
	}

	// Алгоритм Прима-Краскала
	void primCraskal(int& result) {
		// Массив раскрасок вершин
		int* colors = new int[n];
		for (int i = 0; i < n; i++)
			colors[i] = i;

		// Массив ребер, принадлежащих минимальному остовного дереву
		int** edges = new int* [2];
		edges[0] = new int[n - 1];
		edges[1] = new int[n - 1];

		result = 0;

		// Основной цикл алгоритма
		for (int i = 0; i < n - 1; i++) {
			// Поиск минимального ребра
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
			// Запись ребер
			edges[0][i] = minX;
			edges[1][i] = minY;
			// Перекрашивание вершин
			for (int j = 0; j < n; j++) {
				if (j == minX || j == minY) {
					int current = colors[j];
					for (int k = 0; k < n; k++) {
						if (colors[k] == current)
							colors[k] = minX;
					}
				}
			}
			// Подсвет суммы нагрузок ребер остова
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