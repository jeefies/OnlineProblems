// #include <complex>
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

void FFT(Vector &v, int n, int inv) {
	if (n == 1) return; // �ݹ�߽磬ֻ��һ��Ԫ�أ������任
	
	// ��ż�仯Ϊ��������
	int mid = n >> 1;
	Vector even(mid), odd(mid);
	for (int i(0); i < n; i += 2) {
		even[i >> 1] = v[i], odd[i >> 1] = v[i + 1]; 
	}
	// �ݹ���� 
	FFT(even, mid, inv), FFT(odd, mid, inv);
	
	// ���кϲ�����
	// ������� omega
	Complex omega(cos(PI * 2 / n), inv * sin(PI * 2 / n));
	// ��ǰ��ת����
	Complex w(1, 0);
	for (int i(0); i < mid; ++i, w = w * omega) {
		v[i] = even[i] + w * odd[i];
		v[i + mid] = even[i] - w * odd[i];
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	int n, m;
	std::cin >> n >> m;
	
	// ��ȡ���յĳ��ȣ������� 2 �Ĵ��ݣ��ұ���������������Ҫ�� 
	int O(1);
	while (O <= m + n) O <<= 1;
	// std::cout << PI << " " << O << std::endl;
	
	Vector A(O), B(O);
	for (int i(0); i <= n; ++i) std::cin >> A[i].real; 
	for (int i(0); i <= m; ++i) std::cin >> B[i].real;
	
	FFT(A, O, 1);
	FFT(B, O, 1);
	
	// ���ǵ�����ˣ�Ȼ�������任�����ÿһ���ϵ��
	for (int i(0); i < O; ++i) A[i] = A[i] * B[i];
	FFT(A, O, -1);
	
	// ���������
	// �ǵ���������������֮���� n + m �ε�
	for (int i(0); i <= n + m; ++i) {
		// ����������ȡ���� 
		std::cout << (long long)(A[i].real / O + 0.5) << ' ';
	} std::cout << std::flush;
	return 0;
}
