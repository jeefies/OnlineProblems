#include <iostream>

#define sgn(x) (x>0?1:-1)
#define abs(x) (x>0?x:-x)

int main() {
	long long a, b;
	scanf("%lld %lld", &a, &b);
	if (b > 0) printf("%lld", abs(a));
	else printf("%lld", -abs(a));
}
