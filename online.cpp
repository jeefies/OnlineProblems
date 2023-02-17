#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 5;

template<typename T>
inline T gcd(T x, T y) {
	T z;
	while (y) z = x % y, x = y, y = z;
	return x;
}

int qpow(int a, int n, int p)
{
    int ans = 1;
    a %= p;
    while (n)
    {
        if (n & 1)
            ans = ans * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return ans;
}
int phi[MAXN];
bool isnp[MAXN];
vector<int> primes; // 质数表
void init(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!isnp[i])
            primes.push_back(i), phi[i] = i - 1; // 性质1，指数为1的情形
        for (int p : primes)
        {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
            {
                phi[p * i] = phi[i] * p; // 性质2
                break;
            }
            else
                phi[p * i] = phi[p] * phi[i]; // 这时肯定互质，用性质3
        }
    }
}
vector<int> factorize(int a) // 分解质因数
{
    vector<int> v;
    for (int i = 1; i * i <= a; ++i)
        if (a % i == 0)
        {
            v.push_back(i);
            if (i * i != a)
                v.push_back(a / i);
        }
    return v;
}
bool exist[MAXN]; // 是否存在原根
void init_exist() // 初始化exist数组
{
    exist[2] = exist[4] = true;
    for (int i = 1; i < (int)primes.size(); ++i)
    {
        int p = primes[i];
        for (int q = p; q < MAXN; q *= p)
        {
            exist[q] = true;
            if (q * 2 < MAXN)
                exist[q * 2] = true;
        }
    }
}
vector<int> get_primative_roots(int m)
{
    vector<int> v;
    if (!exist[m])
        return v;
    int phiM = phi[m], fst;
    vector<int> factors = factorize(phiM);
    for (int i = 1;; ++i)
    {
        if (gcd(i, m) != 1)
            continue;
        if (qpow(i, phiM, m) != 1)
            continue;
            
        cout << "Checking at " << i << endl;
        
		bool ok = true;
        for (auto e : factors)
            if (e != phiM && qpow(i, e, m) == 1)
            {
                ok = false;
                break;
            }
        if (ok)
        {
            fst = i;
            cout << i << " Valid!" << endl;
            break;
        }
    }
    int cur = fst;
    for (int i = 1; i <= phiM; ++i)
    {
        if (gcd(phiM, i) == 1)
            v.push_back(cur);
        cur = cur * fst % m;
    }
    return v;
}
signed main()
{
	// freopen("P6091_1.in", "r", stdin);
    ios::sync_with_stdio(false);
    init(1e6);
    init_exist();
    cout << "Init ok " << endl;
    int t;
    cin >> t;
    while (t--)
    {
        int n, d;
        cin >> n >> d;
        
        cout << "At " << n << ' ' << d << endl;
        
        vector<int> v = get_primative_roots(n);
        sort(v.begin(), v.end());
        cout << v.size() << endl;
        for (int i = 0; i < v.size(); ++i)
            if (i % d == d - 1)
                cout << v[i] << " ";
        cout << endl;
    }
    return 0;
}