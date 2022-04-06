// Repeat including protect
#ifndef GRAPH
#define GRAPH

// Graph interface
class graph
{
private:
	int** matrix;
	int n;
public:
	graph();
	void init(int** matrix, int n);
	void clear();
	void dijkstra(int& result, int* path, int start, int finish);
	void primCraskal(int** frame);
	void floyd(int& result, int start, int finish);
};

#endif // !GRAPH