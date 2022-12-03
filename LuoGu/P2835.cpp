#include <iostream>

const int N = 202;

class MergeFindSet {
private:
    int grp[N], grpC;
public:
    MergeFindSet() {
        for (int i = 1; i < N; ++i) grp[i] = i;
    }

    void setGrpC(int c) {
        grpC = c;
    }

    int getGrpC() {
        int cnt;
        for (int i = 1; i <= grpC; ++i) {
            if (grp[i] == i) ++cnt;
        }
        return cnt;
    }

    void merge(int x, int y) {
        grp[y] = find(x);
    }

    int find(int x) {
        if (grp[x] != x) return grp[x] = find(grp[x]);
        return x;
    }
};

int n;
int mp[N][N];
void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                mp[i][j] = mp[i][j] || (mp[i][k] && mp[k][j]);
    }
}

int countBlocks() {
    static MergeFindSet mfs; mfs.setGrpC(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mp[i][j]) mfs.merge(i, j);
        }
    }
    return mfs.getGrpC();
}

int main() {
    scanf("%d", &n);

    int t;
    for (int i = 1; i <= n; ++i) {
        while (true) {
            scanf("%d", &t);
            if (t) mp[i][t] = true;
            else break;
        }
    }

    floyd();

    std::cout << countBlocks() << '\n';
}