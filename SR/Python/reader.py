import networkx as nx
from the_traffic_magic import get_pareto_traffic

G = nx.Graph()
with open('p2p-Gnutella04_Nodes_10876_edges_39994.txt', 'r') as f:
    for line in f:
        l = [each.strip() for each in line.strip().split('\t')]
        G.add_edge(l[0], l[1])
nodes = G.nodes()
import itertools

mapping = {value: int(value) for value in nodes}

G = nx.relabel_nodes(G, mapping, copy=False)

nodes = G.nodes()
edges = G.edges()




edge_dict = {}
edge_traffic = {}


def initialize_edge_traffic():
    global edge_traffic
    for each in edges:
        edge_traffic[each] = 0


def update_edge_traffic(val1, val2, traffic):
    global edge_traffic
    if (val1, val2) in edge_traffic.keys():
        edge_traffic[(val1, val2)] += traffic
    elif (val2, val1) in edge_traffic.keys():
        edge_traffic[(val2, val1)] += traffic
    else:
        print('Poda mone dinesha')
        raise Exception


def initialize_edge_dict():
    global edge_dict
    for each in edges:
        edge_dict[each] = []


initialize_edge_dict()
initialize_edge_traffic()


def add_to_edge_list(val1, val2, id):
    global edge_dict
    if (val1, val2) in edge_dict.keys():
        edge_dict[(val1, val2)].append(id)
    elif (val2, val1) in edge_dict.keys():
        edge_dict[(val2, val1)].append(id)
    else:
        print('Entha mone dinesha')
        raise Exception


n = len(nodes)
n_c_2 = n * (n - 1) / 2


totoal_1 = (n * (n - 1) / 2)
print()
pareto_traffic = get_pareto_traffic(1, 20, totoal_1, '.', write_to_file=False)
sd_ids = {}
i = 0
y = 0
for node in nodes:
    paths = nx.single_source_shortest_path(G, node)
    print(n-y)
    y += 1
    for path in paths:
        if path > node:
            now = paths[path]
            # print(now)
            z = n - node
            id = int(n_c_2 - (z * (z - 1) / 2) + path)
            traffic = pareto_traffic[i]
            i += 1
            sd_ids[id] = ((now[0], now[1]), (now[-2], now[-1]))
            for o in range(len(now) - 1):
                value = now[o:o + 2]
                add_to_edge_list(value[0], value[1], id)
                update_edge_traffic(value[0], value[1], traffic)

edge_order = list(edge_dict.keys())
#
# def write_a(edge_order, name):
#     global edge_dict
#     with open(name, 'wb') as f:
#         for each in edge_order:
#             f.write((str(x) for x in edge_order[each]))
#             f.write('\n')
#
# write_a(edge_order, 'a.txt')