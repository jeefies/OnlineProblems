INF = 0x7FFFFFFF

class Graph:
    def __init__(self, n):
        self.n = n
        self.g = tuple([] for i in range(n + 1))
        self.pos = [None for i in range(n + 1)]
    
    def set(self, i, x, y):
        self.pos[i] = (x, y)

    def add(self, u, v):
        dx, dy = self.pos[u][0] - self.pos[v][0], self.pos[u][1] - self.pos[v][1]
        d = (dx * dx + dy * dy) ** 0.5
        self.g[u].append((v, d))
        self.g[v].append((u, d))

    def SPFA(self, s, block):
        inq, dis = [False] * (self.n + 1), [INF] * (self.n + 1)
        pre = [0] * (self.n + 1)
        dis[s] = 0
        q, head = [(s, 0)], 0

        while head < len(q):
            (x, d), head = q[head], head + 1
            inq[x] = False
            for y, w in self.g[x]:
                if y != block[x] and x != block[x] and dis[y] > d + w:
                    dis[y] = d + w
                    pre[y] = x
                    if not inq[y]:
                        q.append((y, dis[y]))
                        inq[y] = True
        # end bfs
        # print(dis, pre)
        return dis, pre
    
    def work(self):
        sec = INF
        block = [0] * (self.n + 1)
        dis, pre = self.SPFA(1, block)

        c = self.n
        while c != 1:
            p = pre[c]
            block[c], block[p] = p, c
            ndis, _ = self.SPFA(1, block)
            sec = min(sec, ndis[self.n])
            block[c], block[p], c = 0, 0, p

        return sec if sec != INF else -1

def main():
    n, m = map(int, input().split())
    g = Graph(n)

    for i in range(n):
        x, y = map(float, input().split())
        g.set(i + 1, x, y)

    for i in range(m):
        u, v = map(int, input().split())
        g.add(u, v)
    
    print(f"{g.work():.2f}")

if __name__ == "__main__":
    main()