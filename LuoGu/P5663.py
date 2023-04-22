INF = 0x7FFFFFFF

class Graph:
    def __init__(self, n):
        self.n = n
        self.g = tuple([] for i in range(n + 1))

    def add(self, u, v):
        self.g[u].append(v)
        self.g[v].append(u)
    
    def SPFA(self, s):
        dis = tuple([INF, INF] for i in range(self.n + 1))
        inq = tuple([False, False] for i in range(self.n + 1))

        head, dis[s][0], q = 0, 0, [(s, 0)]

        while (head < len(q)):
            (x, t), head = q[head], head + 1
            inq[x][t] = False
            for y in self.g[x]:
                if dis[y][0] > dis[x][1] + 1:
                    dis[y][0] = dis[x][1] + 1
                    if not inq[y][0]:
                        inq[y][0] = True
                        q.append((y, 0))
                if dis[y][1] > dis[x][0] + 1:
                    dis[y][1] = dis[x][0] + 1
                    if not inq[y][1]:
                        inq[y][1] = True
                        q.append((y, 1))
        # end bfs

        # for graph is not connected!
        if len(self.g[s]) == 0:
            dis[s][0] = INF
            
        self.dis = dis

    def check(self, x, l):
        return "Yes" if l >= self.dis[x][l & 1] else "No"

def main():
    n, m, q = map(int, input().split())

    g = Graph(n)
    for i in range(m):
        u, v = map(int, input().split())
        g.add(u, v)

    g.SPFA(1)
    for i in range(q):
        x, l = map(int, input().split())
        print(g.check(x, l))

if __name__ == "__main__":
    main()