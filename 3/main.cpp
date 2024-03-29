#include <iostream>
#include <iomanip>



struct SLAU
{
	float** matr;
	float* free;
};

void printSLAU(SLAU* a, unsigned n);

float* gauss(SLAU* a, int n)
{
	float *x, max;
	int k, index;
	const float eps = 0.001;  // точность
	x = new float[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a->matr[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a->matr[i][k]) > max)
			{
				max = abs(a->matr[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			std::cout << "Решение получить невозможно из-за нулевого столбца ";
			std::cout << index << " матрицы A" <<std::endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a->matr[k][j];
			a->matr[k][j] = a->matr[index][j];
			a->matr[index][j] = temp;
		}
		double temp = a->free[k];
		a->free[k] = a->free[index];
		a->free[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a->matr[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a->matr[i][j] = a->matr[i][j] / temp;
			a->free[i] = a->free[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a->matr[i][j] = a->matr[i][j] - a->matr[k][j];
			a->free[i] = a->free[i] - a->free[k];
		}
		k++;
	}
	printSLAU(a, n);
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = a->free[k];
		for (int i = 0; i < k; i++)
			a->free[i] = a->free[i] - a->matr[i][k] * x[k];
	}
	return x;
}

SLAU* createMatr(unsigned n)
{
	SLAU* A;
	A = new SLAU;

	unsigned i, j;

	A->matr = new float*[n];
	A->free = new float[n];

	for (i = 0; i < n; i++) 
	{
		A->matr[i] = new float[n];
		for (j = 0; j < n; j++)
		{
			std::cout << "a[" << i << "][" << j << "] = ";
			std::cin >> A->matr[i][j];
		}
		std::cout << "Св. коэффициент = ";
		std::cin >> A->free[i];
	}
	return A;
}
SLAU* createDefaultSLAU()
{
	SLAU *A;
	A = new SLAU;
	const unsigned n = 5;

	float b[n][n] = {
		{0.72, -0.03, -0.96, -0.69, -0.57 },
		{-0.64, 0.57, 0.52, 0.19, -0.48 },
		{-0.37, 0.38, -0.22, 0.82, 0.28},
		{-0.08, 0.75, 0.05, 0.96, 0.00},
		{0.9, 0.25, -0.39, 0.22, 0.29}
	};

	float c[n] = { 0.77, 0.30, 0.43, 0.82, -0.34 };

	A->matr = new float*[n];
	A->free = new float[n];

	for (unsigned i = 0; i < n; i++)
	{
		A->matr[i] = new float[n];
		for (unsigned j = 0; j < n; j++)
		{
			A->matr[i][j] = b[i][j];
		}
		A->free[i] = c[i];
	}
	return A;
}

SLAU* initSLAU(unsigned n)
{
	SLAU *A;
	A = new SLAU;
	unsigned i;
	
	A->matr = new float*[n];
	A->free = new float[n];
	for (i = 0; i < n; i++)
	{
		A->matr[i] = new float[n];
	}
	return A;
}

void printSLAU(SLAU* a, unsigned n)
{
	unsigned i, j;
	std::cout << std::fixed;
	std::cout.precision(2);

	std::cout << std::endl;
	for (i = 0; i < n; i++)
	{
		if (a->matr[i][0] >= 0)
		{
			std::cout.width(5);
			std::cout << std::setprecision(2) << abs(a->matr[i][0]);
			std::cout << "x" << 1;
		}
		else
		{
			std::cout << "-";
			std::cout.width(4);
			std::cout << std::setprecision(2) << abs(a->matr[i][0]);
			std::cout << "x" << 1;
		}
		for (j = 1; j < n; j++)
		{
			if (a->matr[i][j] >= double(0))
			{
				std::cout << " + ";
				std::cout.width(4);
				std::cout << std::setprecision(2) << abs(a->matr[i][j]);
				std::cout << "x" << j + 1;
			} 
			else
			{
				std::cout << " - ";
				std::cout.width(4);
				std::cout << std::setprecision(2) << abs(a->matr[i][j]);
				std::cout << "x" << j + 1;
			}
			//std::cout << a->matr[i][j]<<" ";
		}
		std::cout << " = ";
		std::cout.width(5);
		std::cout<<std::setprecision(2)<<a->free[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	system("chcp 1251");
	unsigned n = 5;
	float* x;
	SLAU *a;
	
	a = createDefaultSLAU();
	printSLAU(a, 5);
	x = gauss(a, n);

	std::cout << "X = ";
	for (unsigned i = 0; i < n; i++)
	{
		std::cout << x[i] << ", ";
	}

	return 0;
}