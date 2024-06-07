#include <iostream>
#include <vector>
#include <locale.h>
#include <cmath>
//#include <algorithm>
//#include <time.h>

const double PI = 3.14159265;

using namespace std;

class Circle {
	int radius;
	vector <int> center;

public:
	Circle(int radius, vector <int> center) {
		this->radius = radius;
		this->center = center;
	}

	void print() {
		cout << "Радиус = " << radius << " Координаты (" << center[0] << ',' << center[1] << ")" << endl;
	}

	void movingY(int quantity) {
		center[1] += quantity;
	}

	void movingX(int quantity) {
		center[0] += quantity;
	}


	void resize(int quantity) {
		radius += quantity;
	}
};


class Rectangle {
	vector <vector <double>> vertices;
	vector <double> center;
	int length, width;

public:
	Rectangle(vector <vector <double>> vertices) {
		if (!isRectangle(vertices))
			throw invalid_argument("координаты вершин некорректны!");

		this->vertices = vertices;
		length = sqrt(pow(vertices[1][0] - vertices[0][0], 2) + pow(vertices[1][1] - vertices[0][1], 2));
		width = sqrt(pow(vertices[3][0] - vertices[1][0], 2) + pow(vertices[3][1] - vertices[1][1], 2));
		center = { (vertices[0][0] + vertices[1][0]) / 2.0, (vertices[0][1] + vertices[2][1]) / 2.0 };
	}

	bool isRectangle(vector <vector <double>>& vertices) {
		if (vertices.size() != 4)
			return false;

		vector<double> diagonal1 = { vertices[2][0] - vertices[1][0], vertices[2][1] - vertices[1][1] };
		vector<double> diagonal2 = { vertices[3][0] - vertices[0][0], vertices[3][1] - vertices[0][1] };

		double lengthDiagonal1 = sqrt(pow(diagonal1[0], 2) + pow(diagonal1[1], 2));
		double lengthDiagonal2 = sqrt(pow(diagonal2[0], 2) + pow(diagonal2[1], 2));
		if (lengthDiagonal1 != lengthDiagonal2)
			return false;

		return true;
	}

	void print() {
		cout << "Длина = " << length << " | Ширина = " << width << " Координаты центра (" << center[0] << ", " << center[1] << ")" << endl;
	}

	void printVertices() {
		cout << "Вершины:" << endl;
		for (size_t i = 0; i < vertices.size(); i += 2) {
			cout << '(' << vertices[i][0] << ", " << vertices[i][1] << ')';
			if (i + 1 < vertices.size()) {
				cout << "\t\t\t(" << vertices[i + 1][0] << ", " << vertices[i + 1][1] << ')';
			}
			cout << endl;
		}
	}

	void movingY(int quantity) {
		for (auto& vertex : vertices) {
			vertex[1] += quantity;
		}
		center[1] += quantity;
	}

	void movingX(int quantity) {
		for (auto& vertex : vertices) {
			vertex[0] += quantity;
		}
		center[0] += quantity;
	}

	void resizeX(double quantity) {
		length += quantity;

		vertices[1][0] += quantity;
		vertices[3][0] += quantity;

		center[0] += quantity / 2.0;
	}

	void resizeY(double quantity) {
		width += quantity;

		vertices[0][1] += quantity;
		vertices[1][1] += quantity;

		center[1] += quantity / 2.0;
	}

	void rotate(double angle) {
		angle = fmod(angle, 180.0);

		double cosAngle, sinAngle;
		cosAngle = cos(angle * PI / 180.0);
		sinAngle = sin(angle * PI / 180.0);

		double xCenter = center[0];
		double yCenter = center[1];
		movingX(-xCenter);
		movingY(-yCenter);

		double x, y;
		for (auto& vertex : vertices) {
			x = vertex[0]; y = vertex[1];
			
			vertex[0] = x * cosAngle - y * sinAngle;
			vertex[1] = x * sinAngle + y * cosAngle;
		}

		movingX(xCenter);
		movingY(yCenter);
	}

};

class Square : public Rectangle {
public:
	Square(vector <vector <double>> vertices) : Rectangle(vertices) {
		if (!isSquare(vertices))
			throw invalid_argument("координаты вершин некорректны!");
	}

	bool isSquare(vector <vector <double>>& vertices) {
		double side1 = sqrt(pow(vertices[1][0] - vertices[0][0], 2) + pow(vertices[1][1] - vertices[0][1], 2));
		double side2 = sqrt(pow(vertices[3][0] - vertices[1][0], 2) + pow(vertices[3][1] - vertices[1][1], 2));
		double side3 = sqrt(pow(vertices[3][0] - vertices[2][0], 2) + pow(vertices[3][1] - vertices[2][1], 2));
		double side4 = sqrt(pow(vertices[0][0] - vertices[2][0], 2) + pow(vertices[0][1] - vertices[2][1], 2));
		return ((side1 == side2) && (side2 == side3) && (side3 == side4));
	}

};



int main() {
	setlocale(LC_ALL, "Rus");
	try {


		cout << "Круг: " << endl;

		std::vector<int> center = { 2 , 3 };
		int radius = 5;
		Circle k1(radius, center);

		k1.print();

		k1.movingY(5);
		k1.resize(5);

		k1.print();


		// Прямоугольник
		cout << endl;
		cout << "Прямоугольник: " << endl;

	
		vector <vector<double>> vertices = { {2, 6}, {4, 6}, {2, 2}, {4, 2} };
		Rectangle k2(vertices);
		k2.print();
		k2.printVertices();

		cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;

	
		k2.rotate(90);
		k2.print();
		k2.printVertices();

		// Квадрат
		cout << endl;
		cout << "Квадрат: " << endl;

	
		vertices = { {2, 6}, {6, 6}, {2, 2}, {6, 2} };
		Square k3(vertices);
		k3.print();
		k3.printVertices();

	}
	catch (const invalid_argument& e) {
		cerr << "Неверный ввод: " << e.what() << endl;
	}

	
}