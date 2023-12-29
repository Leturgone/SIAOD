#include <iostream>
#include <vector>
using namespace std;
//Матрица смежности
//1) Определить количество простых циклов в графе.
//2) Найти кратчайший путь между двумя заданными вершинами графа.
struct Edge {
	int u; // вершина, из которой идет ребро
	int v; // вершина, в которую идет ребро
	int weight; // вес ребра
};
class Graph {
private:
	vector<vector<Edge>> SMatrix; // Матрица смежности, ребра графа
public:
	Graph(int size) {
		SMatrix.resize(size);
	}
	// Добавление ребра в матрицу смежности
	void add_edge(int u, int v, int weight) {
		Edge e{ u, v, weight };
		SMatrix[u].push_back(e);
		SMatrix[v].push_back(e);
	}

	void print_graph() {
		int size = SMatrix.size();
		for (int i = 0; i < size; i++) {
			cout << "Вершина " << i << ": ";

			for (int j = 0; j < SMatrix[i].size(); j++) {
				if (SMatrix[i][j].v == i) {
					cout << SMatrix[i][j].u << " (" << SMatrix[i][j].weight << ") ";
				}
				else {
					cout << SMatrix[i][j].v << " (" << SMatrix[i][j].weight << ") ";
				}
			}

			cout << std::endl;
		}
	}

	// 1) Определить количество простых циклов в графе.
	int find_cycle(int start, int current, std::vector<bool>& visited) {
		int count = 0;
		visited[current] = true;

		for (int i = 0; i < SMatrix[current].size(); i++) {
			Edge e = SMatrix[current][i];
			int next = (e.u == current) ? e.v : e.u;

			if (next == start) {
				count++;
			}
			else if (!visited[next]) {
				count += find_cycle(start, next, visited);
			}
		}

		visited[current] = false;
		return count;
	}

	int count_simple_cycles() {
		int size = SMatrix.size();
		int count = 0;

		for (int i = 0; i < size; i++) {
			vector<bool> visited(size, false);
			count += find_cycle(i, i, visited);
		}

		return count;
	}
	//2) Найти кратчайший путь между двумя заданными вершинами графа.


};
int main() {
	setlocale(0, "");
	Graph graph(5);
	graph.add_edge(0, 1, 10);
	graph.add_edge(1, 2, 20);
	graph.add_edge(2, 3, 30);
	graph.add_edge(3, 4, 40);
	graph.print_graph();
	cout << graph.count_simple_cycles();

}