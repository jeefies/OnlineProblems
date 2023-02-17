#include <complex>
#include <iostream>
#include <algorithm>
#include <vector>

struct Complex {
	double real, imag;
	Complex() : real(0), imag(0) {}
	Complex(double re, double im) : real(re), imag(im) {};
	inline Complex operator + (const Complex & b) { return Complex(real + b.real, imag + b.imag); }
	inline Complex operator - (const Complex & b) { return Complex(real - b.real, imag - b.imag); }
	inline Complex operator * (const Complex & b) { return Complex(real * b.real - imag * b.imag, real * b.imag + imag * b.real); }
};

typedef std::vector<Complex> Vector;

const double PI = acos(-1);
int O(1), logO(0);

void FFT(std::vector<int> &rev, Vector &v, int inv) {
	for (int i(0); i < O; ++i) {
		if (i < rev[i]) std::swap(v[i], v[rev[i]]);
	}
	
	// 第 k 次合并，一共logO次 
	for (int k(1); k < O; k <<= 1) {
		Complex omega(cos(PI / k), inv * sin(PI / k));
		for (int i(0); i < O; i += (k<<1)) { // 处理行 
			Complex w(1, 0);
			for (int j = 0; j < k; ++j, w = w * omega) {
				Complex s = v[i + j], t = v[i + j + k] * w;
				v[i + j] = s + t, v[i + j + k] = s - t; 
			}
		}
	}
	
	if (inv == -1) for (int i(0); i < O; ++i) v[i].real /= O;
}


int main() {
	int n, m;
	std::cin >> n >> m;
	
	while (O <= n + m) O <<= 1, ++logO;
	
	Vector A(O), B(O);
	for (int i(0); i <= n; ++i) std::cin >> A[i].real; 
	for (int i(0); i <= m; ++i) std::cin >> B[i].real;
	
	std::vector<int> rev(O);
	for (int i(0); i < O; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logO - 1));
	
	FFT(rev, A, 1), FFT(rev, B, 1);
	
	for (int i(0); i < O; ++i) A[i] = A[i] * B[i];
	FFT(rev, A, -1);
	
	for (int i(0); i <= n + m; ++i) {
		std::cout << (long long)(A[i].real + 0.1) << ' '; // 向上取整 
	} std::cout << std::flush;
	return 0;
}
