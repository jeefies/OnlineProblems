/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <cstring>

using namespace std;

int main() {
	char word[33] = {0};
	cin.getline(word, 32);
	int sl = strlen(word) - 1;
	
	if (sl > 2 && word[sl] == 'r' && word[sl - 1] == 'e') {
		word[sl] = word[sl - 1] = '\0';
	} else if (sl > 2 && word[sl] == 'y' && word[sl - 1] == 'l') {
		word[sl] = word[sl - 1] = '\0';
	} else if (sl > 3 && word[sl] == 'g' && word[sl - 1] == 'n' && word[sl - 2] == 'i') {
		word[sl] = word[sl - 1] = word[sl - 2] = '\0';
	}
	printf("%s\n", word);
}
