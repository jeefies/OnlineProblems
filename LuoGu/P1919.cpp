#include <complex>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

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
	std::string cA, cB;
	std::cin >> cA >> cB;
	
	int n = cA.size(), m = cB.size();
	while (O < n + m) O <<= 1, ++logO;
	
	// std::cout << n << ' ' << m << ' ' << O << ' ' << logO << '\n';
	
	Vector A(O), B(O);
	for (int i(0); i < n; ++i) A[n - i - 1].real = cA[i] - '0'; 
	for (int i(0); i < m; ++i) B[m - i - 1].real = cB[i] - '0';
	
	// for (int i(0); i < O; ++i) std::cout << A[i].real << ' ' << B[i].real << '\n'; 
	
	std::vector<int> rev(O);
	for (int i(0); i < O; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logO - 1));
	
	FFT(rev, A, 1), FFT(rev, B, 1);
	
	for (int i(0); i < O; ++i) A[i] = A[i] * B[i];
	FFT(rev, A, -1);
	
	std::vector<int> ans(O);
	int nm(n + m);
	for (int i(0); i <= nm; ++i) {
		ans[i] += (int)(A[i].real + 0.5);
		if (ans[i] >= 10) ans[i + 1] += ans[i] / 10, ans[i] %= 10, nm += (i == nm);
	}
	while (!ans[nm] && nm) --nm;
	while (nm >= 0) std::cout << ans[nm--];
	return 0;
}
