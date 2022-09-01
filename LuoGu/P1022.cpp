/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1022
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

#define OPE 0
#define NUM 1

class Node {
public:
	bool isNegetive; // only useful when parsing the string
	bool isUnknown; // have any not numeric char
	int val;
	Node(bool isN = false, bool isU = false, int v = 0) {
		isNegetive = isN, isUnknown = isU , val = v;
	}

	Node & operator+=(const Node & o) {
		val += o.val;
		return *this;
	}

	char print(bool newline = true) {
		cout << "Node(" << isUnknown << ", " << val << ")";
		if (newline) return '\n';
		return ' ';
	}
};

int main() {
	string str;
	cin >> str;

	// 左边放未知数，右边放常数项
	Node left, right;

	int i = 0;
	// 标记正在解析等式的左边还是右边
	bool atleft = true;
	// 当前正在解析的部分（带符号）
	Node tmp;
	// 未知变量名
	string unknownVar;
	bool getUnkonwnVar = false;

	while (i < str.size()) {
		// 判断是否跳到等式右侧
		if (str[i] == '=') {
			atleft = false, ++i;
		}

		// 先判断符号
		tmp.isNegetive = false;
		if (str[i] == '-') tmp.isNegetive = true, ++i;
		// 不用else防止没有符号的情况
		else if (str[i] == '+') ++i;

		// ui指未知数名字开始的地方，val是常数项或一次项系数的知
		int ui, val = 0;
		// 标记是否为一次未知项
		tmp.isUnknown = false;
		// 到+-=符号结束
		for (i = i; i < str.size() && str[i] != '-' && str[i] != '+' && str[i] != '='; i++) {
			if ('0' <= str[i] && str[i] <= '9') val = val * 10 + str[i] - '0';
			else if (!tmp.isUnknown && (str[i] < '0' || str[i] > '9')) tmp.isUnknown = true, ui = i;

		}

		// 如果一次项前面没有显式的系数，则需要把系数设为1
		tmp.val = val == 0 && tmp.isUnknown ? 1 : val;
		// 如果有负号，则把值去相反数
		if (tmp.isNegetive) tmp.val = -tmp.val;

		// 保存未知数信息
		if (tmp.isUnknown && !getUnkonwnVar) unknownVar = str.substr(ui, i - ui), getUnkonwnVar = true;

		if (atleft) {
			if (tmp.isUnknown) left += tmp;
			else {
				tmp.val = -tmp.val;
				right += tmp;
			}
		} else {
			if (!tmp.isUnknown) right += tmp;
			else {
				tmp.val = -tmp.val;
				left += tmp;
			}
		}
	}

	double r = (double)right.val / (double)left.val;
	// 如果常数项合并之后是0.则需要额外处理
	if (right.val == 0) r = 0;
	printf("%s=%.3lf\n", unknownVar.c_str(), r);
}
