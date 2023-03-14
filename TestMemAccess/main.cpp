#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;

struct square {
	int n;
	double* data;
	int *index;
	square(int _n) : n(_n) {
		int sz = n * n;
		data = new double[sz];
		memset(data, 0, sz * sizeof(double));

		index = new int[n];
		for (int i = 0; i < n; i++) {
			index[i] = i;
		}

		unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(index, index, std::default_random_engine(seed));
	}

	~square() {
		delete[] data;
		delete[] index;
	}
};


double row_major(square* c) {
	double s = 0;
	for (int y = 0; y < c->n; y++) {
		for (int x = 0; x < c->n; x++) {
			s += c->data[y * c->n + c->index[x]];
		}
	}
	return s;
}

double column_major_process(square* c) {
	double s = 0;
	for (int x = 0; x < c->n; x++) {
		for (int y = 0; y < c->n; y++) {
			s += c->data[c->index[y] * c->n + x];
		}
	}
	return s;
}

double measure_running_time(double (*fx)(square*), square* c, int n) {
	double s = 0;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		s += fx(c);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> t = end - start;
	double x = t.count();
	if (s == 0) {
		return x;
	}
	return -1;
}

double test(int n, int nsteps) {
	auto sq = std::make_shared<square>(n);
	auto t1 = measure_running_time(row_major, sq.get(), nsteps);
	if (t1 < 0) {
		return -1;
	}
	auto t2 = measure_running_time(column_major_process, sq.get(), nsteps);
	if (t2 < 0) {
		return -1;
	}
	return t2 / t1;
}

int main(int argc, char *argv[]) {
	int n = 100;
	int nsteps = 100000;
	if (argc > 1) {
		n = atoi(argv[1]);
		if (n < 1) {
			cerr << "the size of square matrix must be greater than 0.\n";
			return -1;
		}
	}

	if (argc > 2) {
		nsteps = atoi(argv[2]);
		if (n < 1) {
			cerr << "the number of steps must be greater than 0.\n";
			return -1;
		}
	}
	cout << test(n, nsteps);
	return 0;
}