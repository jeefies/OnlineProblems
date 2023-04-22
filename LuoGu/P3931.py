class Graph:
    def __init__(self, n, s):
        self.g = tuple([] for i in range(n + 1))
        self.vis = [False] * (n + 1)

    def add(self, u, v, c):
        self.g[u].append((v, c))
        self.g[v].append((u, c))

    def dp(self, x):
        cost = 0
        self.vis[x] = True
        isLeaf = True
        for y, c in self.g[x]:
            if self.vis[y]: continue
            isLeaf = False
            cost += min(self.dp(y), c)
        return 1000000000 if isLeaf else cost

def main():
    n, s = map(int, input().split())
    g = Graph(n, s)

    for i in range(n - 1):
        u, v, c = map(int, input().split())
        g.add(u, v, c)

    print(g.dp(s))

if __name__ == "__main__":
    main()