import networkx as nx


def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]


def connect_to_db():
    import sqlite3
    conn = sqlite3.connect('att.db')
    c = conn.cursor()
    return c, conn


def graph_open():
    G = nx.Graph()
    with open('p2p-Gnutella04_Nodes_10876_edges_39994.txt', 'r') as f:
        for line in f:
            l = [each.strip() for each in line.strip().split('\t')]
            G.add_edge(l[0], l[1])
    return G


def initialize_edge_traffic(G):
    global edge_traffic
    edge_traffic = {edge: 0 for edge in G.edges()}
    # for each in G.edges():
    #     edge_traffic[each] = 0


class EdgeNames:
    def __init__(self, edges):
        self.i = 0
        self.edge = {edge: [self.get_counter(), 0] for edge in edges}

    def get_counter(self):
        self.i += 1
        return self.i

    def get_edge_id(self, edge):
        if (edge[0], edge[1]) in self.edge.keys():
            return self.edge[edge][0]
        elif (edge[1], edge[0]) in self.edge.keys():
            return self.edge[edge[1], edge[0]][0]
        else:
            print('whats going on')

    def update_edge_traffic(self, val1, val2, traffic):
        if (val1, val2) in self.edge.keys():
            self.edge[(val1, val2)][1] += traffic
        elif (val2, val1) in self.edge.keys():
            self.edge[(val2, val1)][1] += traffic
        else:
            print('Poda mone dinesha: update_edge_traffic')
            raise Exception

    def get_traffic_on_edge(self, val):
        if (val[0], val[1]) in self.edge.keys():
            return self.edge[(val[0], val[1])][1]
        elif (val[1], val[0]) in self.edge.keys():
            return self.edge[(val[1], val[0])][1]
        else:
            print('Poda mone dinesha: get_traffic_on_edge')
            raise Exception

    def total_traffic(self):
        return [sum(i)for i in zip(*list(self.edge.values()))][1]



def cycle_rem(new_path):
    i = 0
    selected = []
    while i<len(new_path):
        selected.append(new_path[i])
        if new_path[i] in new_path[i+1:]:
            i = i + (new_path[i+1:].index(new_path[i])) + 1
        i += 1
    return selected