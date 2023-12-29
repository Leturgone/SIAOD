#include <iostream>
#include <vector>
using namespace std;
//Матрица смежности
//1) Определить количество простых циклов в графе.
//2) Найти кратчайший путь между двумя заданными вершинами графа.


class Graph {
private:
	vector<vector<int>> SMatrix;//Матрица смежности
public:
	Graph(int size) {
		SMatrix.resize(size, vector<int>(size, 0)); 
	}
	int add_edge(int u, int v, int weight) {//добавление ребра в матрицу смежности
		if (u < SMatrix.size() && v < SMatrix.size()) {
			SMatrix[u][v] = weight;
			SMatrix[v][u] = weight;
			return 0;
		}
		else {
			return 1;
		}
	}

	void print_graph() {
		int size =SMatrix.size();
		for (int i = 0; i < size; i++) {
			cout << "Вершина " << i << ": ";

			for (int j = 0; j < size; j++) {
				if (SMatrix[i][j] != 0) {
					cout << j << " "<<"("<< SMatrix[i][j]<<")"<<" ";
				}
			}

			std::cout << std::endl;
		}
	}
	//1) Определить количество простых циклов в графе.
	int find_cycle(int start, int current,vector<bool>& visited) {
		int count = 0;
		int size = SMatrix.size();
		visited[current] = true;//устанавливаем посещение текущей вершины

		for (int i = 0; i < size; i++) {
			//перебираем все вершины графа
			if (SMatrix[current][i] != 0) {
				if (i == start) {
					count++;
				}
				else if (!visited[i]) {
					count += find_cycle(start, i, visited);
				}
			}
		}

		visited[current] = false;
		return count;
	}
	int count_simple_cycles() {
		int size = SMatrix.size();
		int count = 0;
		for (int i = 0; i < size; i++) {
			vector<bool> visited(size, false);//посещенные вершины
			count += find_cycle(i, i, visited);
		}

		return count;
	}

	//2) Найти кратчайший путь между двумя заданными вершинами графа.
	//Используется алгоритм дейикстры
	void shortest_path_di(int start, int end) {
		//Инициализация
		vector<int> marks(SMatrix.size(), 1000000);//Вектор для меток расстояня
		marks[start] = 0;// Расстояние от стартовой вершины до себя равно нулю

		vector<bool> visited(SMatrix.size(), false);//Вектор для хранения информации о посещении вершин
		vector<int> previous(SMatrix.size(), -1);//Вектор для хранения информации о предыдущей вершине на пути

		for (int i = 0; i < SMatrix.size(); i++) {
			int min_mark = 1000000;
			int min_verind=0;
			// Найти вершину с минимальным расстоянием, которая еще не была посещена
			for (int j = 0; j < SMatrix.size(); j++) {
				if (!visited[j] && marks[j] < min_mark) {
					min_mark = marks[j];
					min_verind = j;
				}
			}
			// Пометить найденную вершину как посещенную
			visited[min_verind] = true;

			// Обновить расстояния до соседних вершин
			for (int j = 0; j < SMatrix.size(); j++) {
				if (SMatrix[min_verind][j] != 0 && marks[min_verind] + SMatrix[min_verind][j] < marks[j]) {
					marks[j] = marks[min_verind] + SMatrix[min_verind][j];
					previous[j] = min_verind;
				}
			}
		}
		//Вывод пути
		vector<int> path;
		int current = end;
		while (current != start) {
			path.insert(path.begin(), current);
			current = previous[current];
		}
		path.insert(path.begin(), start);

		cout << "Кратчайший путь: ";
		for (int i = 0; i < path.size(); i++) {
			cout << path[i];
			if (i != path.size() - 1) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
};




int main() {
	setlocale(0, "");
	int size = 10;
	Graph graph(size);
	graph.add_edge(1, 2,2);
	graph.add_edge(1, 3,6);
	graph.add_edge(1, 4, 4);
	graph.add_edge(2, 4, 7);
	graph.add_edge(2, 5, 8);
	graph.add_edge(3, 4, 8);
	graph.add_edge(3, 6, 5);
	graph.add_edge(4, 6, 8);
	graph.add_edge(4, 5, 2);
	graph.add_edge(5, 6, 4);
	//graph.add_edge(0, 2, 3);
	//graph.add_edge(0, 1, 11);
	//graph.add_edge(1, 2, 2);

	graph.print_graph();
	cout << "---Меню работы с графом---" << endl;
	cout << "1.Добавть ребро в граф"<<endl<<"2.Найти количество простых циклов" << endl << "3.Найти кротчайший путь между двумя вершинами" << endl<<"4.Вывести граф"<<endl << "5.Выйти из программы"<<endl;
	while (true) {
		int n;
		cout << "Выберите номер операции: ";
		if (cin >> n) {
			if (n == 1) {
				int u, v, w;
				cout << "Введите 2 вершины и вес ребра: " << endl;
				if (cin >> u >> v >> w) {
					if (graph.add_edge(u, v, w) == 0) {
						cout << "Ребро добавлено успешно" << endl;
					}
					else {
						cout << "Ошибка при добавлении ребра" << endl;
					}
				}
				else {
					cout << "Введено неверно" << endl;
				}
			}
			else if (n == 2) {
				cout << "Количество простых циклов :" << graph.count_simple_cycles() << endl;

			}
			else if (n == 3) {
				int n1, n2;
				if (cin >> n1 >> n2) {
					if (n1 < size and n2 < size) {
						graph.shortest_path_di(n1, n2);
					}
					else {
						cout<<"В графе нет стольких вершин" << endl;
					}
				}
				else {
					cout << "Введено неверно" << endl;
				}
			}
			else if (n == 4) {
				graph.print_graph();
			}
			else if (n == 5) {
				cout << "Выполнен выход из программы" << endl;
				return 0;
			}
			else {
				cout << "Операции под таким номером нет в списке, повторите ввод" << endl;
			}
		}
		else {
			cin.clear();
			while (cin.get() != '\n') {
				cout << "Введено неверно, повторите попытку" << endl;

			}
		}
	}
	return 0;
}