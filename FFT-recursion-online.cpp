//LuoguP3803
#include <bits/stdc++.h>
const int NR = 1 << 22;
const double eps = 1e-6, pi = acos(-1.0);
using namespace std;
complex<double> a[NR], b[NR]; //complexΪC++�Դ�����
int n, m;
void FFT(complex<double> *a, int n, int inv) //invΪ�鲿���ţ�invΪ1ʱFFT��invΪ-1ʱIFFT
{
    if (n == 1) //�����Ҫת����ֻ��һ���ֱ�ӷ���
        return;
    int mid = n / 2;
    complex<double> A1[mid + 1], A2[mid + 1];
    for (int i = 0; i <= n; i += 2) //��ֶ���ʽ
    {
        A1[i / 2] = a[i];
        A2[i / 2] = a[i + 1];
    }
    FFT(A1, mid, inv); //�ݹ����
    FFT(A2, mid, inv);
    complex<double> w0(1, 0), wn(cos(2 * pi / n), inv * sin(2 * pi / n)); //��λ��
    for (int i = 0; i < mid; ++i, w0 *= wn)                               //�ϲ�����ʽ
    {
        a[i] = A1[i] + w0 * A2[i];
        a[i + n / 2] = A1[i] - w0 * A2[i];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) //�����һ������ʽ
    {
        double x;
        scanf("%lf", &x);
        a[i].real(x); //complex���ͱ���.real(x)��ζ�Ž�ʵ������Ϊx��real()����ʵ����ֵ
    }
    for (int i = 0; i <= m; ++i) //����ڶ�������ʽ
    {
        double x;
        scanf("%lf", &x);
        b[i].real(x);
    }
    int len = 1 << max((int)ceil(log2(n + m)), 1); //����FFT��Ҫ����Ϊ2�������η��������Զ���ʽ����lenΪ��һ������n+m�Ķ����������η�
    FFT(a, len, 1);                                //ϵ�����ת��ֵ���
    FFT(b, len, 1);
    for (int i = 0; i <= len; ++i)
        a[i] = a[i] * b[i];                       //O(n)�˷�
    FFT(a, len, -1);                              //��ֵ���תϵ�����
    for (int i = 0; i <= n + m; ++i)              //���
        printf("%.0f ", a[i].real() / len + eps); //�ǵ�Ҫ��n��epsΪ�������������
    return 0;
}

