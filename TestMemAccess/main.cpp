#include <iostream>
#include <chrono>
using namespace std;

template<class T, int W, int H>
struct container{
	T data[W * H];

	void init() {
		memset(data, 0, W * H * sizeof(T));
	}
};

template<class T, int W, int H>
T process_row(container<T, W, H> *c, int offset) {
	T s = 0;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			int i = (x + offset) % W;
			s += c->data[y * W + i] + c->data[y * W + x];
		}
	}
	return s;
}

template<class T, int W, int H>
T process_column(container<T, W, H>* c, int offset) {
	T s = 0;
	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			int i = (x + offset) % W;
			s += c->data[y * W + i] + c->data[y * W + x];
		}
	}
	return s;
}

template<class T, int W, int H>
void test(const char * tag, double (*fx)(container<T, W, H>*, int), container<T, W, H>* c, int offset, int n = 10) {
	cout << "- start testing '" << tag << "'\n";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < n; i++) {
		fx(c, offset);
	}
	auto dt = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
	cout << "--> done! Elapsed time: " << dt << " ms\n\n";
}


int main() {
	int offset = 1;
	auto c = new container<double, 192000, 1080>;
	c->init();

	test("process_row", process_row, c, offset);
	test("process_column", process_column, c, offset);
	
	delete c;

	return 0;
}