from cyaron import *

n, m = 100, 1000
graph = Graph.DAG(n, m)

io = IO("P4298-gen.in", "P4298-gen.out")
io.input_writeln(n, m)
io.input_writeln(graph.to_str(shuffle = True, output = Edge.unweighted_edge))
