#include <iostream>
#include <vector>
using namespace std;
//������� ���������
//1) ���������� ���������� ������� ������ � �����.
//2) ����� ���������� ���� ����� ����� ��������� ��������� �����.
struct Edge {
	int u; // �������, �� ������� ���� �����
	int v; // �������, � ������� ���� �����
	int weight; // ��� �����
};
class Graph {
private:
	vector<vector<Edge>> SMatrix; // ������� ���������, ����� �����
public:
	Graph(int size) {
		SMatrix.resize(size);
	}
	// ���������� ����� � ������� ���������
	void add_edge(int u, int v, int weight) {
		Edge e{ u, v, weight };
		SMatrix[u].push_back(e);
		SMatrix[v].push_back(e);
	}

	void print_graph() {
		int size = SMatrix.size();
		for (int i = 0; i < size; i++) {
			cout << "������� " << i << ": ";

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

	// 1) ���������� ���������� ������� ������ � �����.
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
	//2) ����� ���������� ���� ����� ����� ��������� ��������� �����.


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