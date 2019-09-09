//	Main function meant to illustrate the use of matrix.h
// In a new project, you only need to copy to your project folder
// and include 'matrix.h' file.

#include "pch.h"
#include <iostream>
#include "matrix.h"

void ShowMatrix(matrix<int> m);

int main()
{
	// Instatiate 3x3 matrix (m) and initialize it with zeroes.
	std::cout << "Instatiate 3x3 matrix (m) and initialize it with zeroes.\n";
	matrix<int> m(3, 3, 0);
	ShowMatrix(m);

	// Fill it with values -> m[i,j] = i+j
	std::cout << "Fill it with values -> m[i,j] = i+j\n";
	for (int i = 0; i < m.Get_size_x(); i++) {
		for (int j = 0; j < m.Get_size_y(); j++) {
			m.SetElement(i, j, i + j);
		}
	}
	ShowMatrix(m);

	// Resize the matrix to 4x4 and insert ones in new rows/columns
	std::cout << "Resize the matrix to 4x4 and insert ones in new rows/columns\n";
	m.Resize(4, 4, 1);
	ShowMatrix(m);

	// Create a new matrix as (n) a copy of 'm'
	std::cout << "Create a new matrix (n) as a copy of 'm'\n";
	matrix<int> n(m);
	ShowMatrix(n);

	// Perform matrix product (p=m*n)
	std::cout << "Perform matrix product (p=m*n)\n";
	matrix<int> p(4, 4, 0);
	p = m * n;
	ShowMatrix(p);

	// Perform vector product with a matrix (v={2,2,2,2})
	std::cout << "Perform vector product with a matrix (v={2,2,2,2})\n";
	std::vector<int> v({ 2, 2, 2, 2 });
	v = m * v;
	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i] << "\t";
	}
	std::cout << std::endl;
}

void ShowMatrix(matrix<int> m) {
	for (int i = 0; i < m.Get_size_x(); i++) {
		for (int j = 0; j < m.Get_size_y(); j++) {
			std::cout << m.GetElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}