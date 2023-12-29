#include <iostream>
#include <vector>
using namespace std;
double St(int x1,int x2,int x3,int y1,int y2,int y3){//площадь треугольника по координатам
	double a = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	double b = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
	double c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	double p = (a + b + c) / 2;
	double s = sqrt(p*(p-a)*(p-b)*(p-c));
	return s;
}
double Sk(int x1, int x2, int x3, int y1, int y2, int y3) {//площадь круга по координатам
	double a = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	double b = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
	double c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	double r = (a * b * c) / (4 * St(x1, x2, x3, y1, y2, y3));
	double S= pow(r, 2) * 3.14;
	return S;
}
void cvector(vector<vector<double>>&X,int x) {//создание вектора
	X.resize(x);
	for (int i = 0; i < x; i++){
		cout << "¬ведите координаты точки (x,y) є" << i << endl;
		X[i].resize(2);
		for (int j = 0; j < 2; j++)
		{
			if (!(cin >> X[i][j])) {
				cin.clear();//чистка
				while (cin.get() != '\n') {
					cout << "¬ведено неверно, повторите попытку" << endl;
					j = j - 1;
				}
			}
		}
	}
}
void veccout(vector<vector<double>> X) {//вывод вектора
    cout << " оординаты точек : \n";
	for (int i = 0; i < X.size(); i++)
	{
		cout << "“очка є" << i<<": ";
		for (int j = 0; j < X[i].size(); j++) {
			cout << X[i][j] << " ";
		}
		cout << endl;
	}
}
void matchS(vector<vector<double>> X) {// нахождение трех различных точек так, чтобы разность между площадью круга, 
//ограниченного окружностью, проход€щей через эти три точки,и площадью треугольника с вершинами в этих точках была минимальной. 
	double min = 100000000000000000;
	int mini = 0;
	int minj = 0;
	int mink=0;
	int l = X.size();
	for (int i = 0; i < l-1; i++) {
		for (int j = i+1; j < l-1; j++) {
			for (int k = j+1; k < l ; k++) {
				double sr = fabs(St(X[i][0], X[j][0], X[k][0], X[i][1], X[j][1], X[k][1]) - Sk(X[i][0], X[j][0], X[k][0], X[i][1], X[j][1], X[k][1]));
				if (sr < min) {
					min = sr;
					mini = i;
					minj = j;
					mink = k;
				}
			}
		}

	}
	vector<vector<double>>X2 = { {X[mini][0],X[mini][1]},{X[minj][0],X[minj][1]},{X[mink][0],X[mink][1]} };
	veccout(X2);
}
int main(){
	vector<vector<double>>v;
	int x, y;
	setlocale(0, "");
	cout << "Ћабораторна€ работа є2 \"ƒвумерный массив\". яснецов ‘Єдор" << endl;
	cout << "«адача на векторе" << endl;
	while (true) {
		cout << "„тобы выйти введите любой другой символ" << endl;
		cout << "¬ведите количество точек на плоскости в множестве,количество точек должно быть больше или равно 3 : ";
		if (cin >> x) {
			if (x >= 3) {
				cvector(v, x);
				veccout(v);
				cout << "–азность между площадью круга,ограниченного окружностью, проход€щей через три точки,и площадью треугольника " << endl;
				cout << "с вершинами в этих точках будет минимальной, если эти точки будут иметь координаты : " << endl;
				matchS(v);
			}
			else {
				cin.clear();
				cout << "¬ведено неверно, повторите попытку" << endl;
			}
		}
		else {
			break;
		}
	}
	return 0;
}