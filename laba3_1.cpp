#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <chrono>
#include <cstdlib>
#include <ctime> 
using namespace std;
#define N 100000
#define M 100000
int y[N];
int u[N];
int request[M];
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
void int_massiv()
{
	// определяем переменные

	int i;

	srand(time(0)); // инициализация генерации случайных чисел

	for (i = 0; i < N; i++) {
		y[i] = -10000 + rand() % 20000;
		u[i] = y[i];
	}

	for (int i = 0; i < M; i++) {
		request[i] = y[i] = -10000 + rand() % 20000;
	}

}
void quicksort(int a, int b, int x[N]) {

	if (a >= b) {
		return;
	}
	int m = (a + b) / 2;
	int k = x[m];
	int l = a - 1;
	int r = b + 1;
	while (true) {
		do { l++; } while (x[l] < k);
		do { r--; } while (x[r] > k);
		if (l >= r) {
			break;
		}
		int tmp = x[r];
		x[r] = x[l];
		x[l] = tmp;
	}
	r++;
	l = l - 1;
	quicksort(a, l, x);
	quicksort(r, b, x);

}

int B_S(int l, int r, int k) {
	if (k < u[l]) {
		return 1000000;
	}
	if (k == u[l])
		return l;
	if (k > u[r]) {
		return 1000000;
	}
	int a = l, b = r;
	while (a + 1 < b) {
		int c = (a + b) / 2;
		if (k > u[c])
			a = c;
		else
			b = c;
	}
	if (u[b] == k)
		return b;
	else {
		return 1000000;
	}
}

int main() {

	setlocale(LC_ALL, "Russian");
	//freopen("output.txt", "w", stdout);
	int_massiv();
	quicksort(0, N - 1, u);
	quicksort(0, N - 1, y);
	Timer t;
	for (int i = 0; i < M; i++) {
		bool flag = false;
		for (int j = 0; j < N; j++) {
			if (request[i] == y[j]) {
				//	cout << j << endl;
				flag = true;
			}
			if (flag) break;
		}
		//	if (!flag) cout << "No solution" << endl;
	}
	cout << "Время линейного: " << t.elapsed() << endl;
	
	Timer d;

	for (int i = 0; i < M; i++) {
		int index = B_S(0, N - 1, request[i]);
		
	}
	cout << "Время бинарного : " << d.elapsed() << endl;

	return 0;
}