extern "C" <%
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
%>

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#define SIZE 100000

int n, w;
int values<:SIZE:>, weights<:SIZE:>, numbers<:SIZE:>;
int dp<:40000:> = <%0%>;

int main(int argc, char * argv<::>) <%
	cin >> n >> w;
	for (int i = 0; i < n; i++) <%
		scanf("%d%d%d", values + i, weights + i, numbers + i);
	%>
	
	for (int i = 0; i < n; i++) <%
		for (int c = 0; i<:numbers:> - (1 << c) >= 0; c++) <%
			int k = i<:numbers:> - (2 << c) >= 0 ? 1 << c : i<:numbers:> - (1 << c) + 1;

			for (int v = w; v >= i<:weights:> * k; v--) <%
				v<:dp:> = max(v<:dp:>, (v - weights<:i:> * k)<:dp:> + i<:values:> * k);
			%>
		%>
	%>
	
	cout << w<:dp:> << endl;
	return 0;
%>