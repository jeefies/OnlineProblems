#include <iostream>
#include <map>

using namespace std;

// N is prime !
const int N = 5e4 + 21, SMOD = 137; 

inline char getToken() {
	char tmp;
	while ((tmp = getchar()) != '#' && tmp != '+' && tmp != '?' && tmp != '$');
	return tmp;
}

class MergeFindSet {
private:
	map<string, string> grp;
public:
	string find(string name) {
		if (name != grp[name]) grp[name] = find(grp[name]);
		return grp[name];
	}

	void merge(string parent, string child) {
		grp[find(child)] = find(parent);
	}

	void init(string name) {
		if (grp[name] == "") grp[name] = name;
	}
};

int main(int argc, char *argv[]) {
	char opt;
	string parent, name;
	static MergeFindSet mfs;
	while ((opt = getToken()) != '$') {
		if (opt == '#') {
			cin >> parent;
			mfs.init(parent);
		} else if (opt == '+') {
			cin >> name;
			mfs.init(name);
			mfs.merge(parent, name);
		} else {
			cin >> name;
			cout << name << ' ' << mfs.find(name) << endl;
		}
	}

	return 0;
}
