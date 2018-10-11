import networkx as nx
import math
from the_traffic_magic import get_pareto_traffic_one
import sqlite3


G = nx.Graph()
with open('p2p-Gnutella04_Nodes_10876_edges_39994.txt', 'r') as f:
    for line in f:
        l = [each.strip() for each in line.strip().split('\t')]
        G.add_edge(l[0], l[1])


def connect_to_db():
    conn = sqlite3.connect('att.db')
    c = conn.cursor()
    return c, conn

def create_tables(c, conn):
    c.execute('''CREATE TABLE Id_Traffic (id real, traffic real)''')
    c.execute('''CREATE TABLE Id_First_Last (id real, first1 VARCHAR, last1 VARCHAR)''')
    conn.commit()

def drop_table(c, conn):
    c.execute('''DROP TABLE Id_Traffic''')
    c.execute('''DROP TABLE Id_First_Last''')
    conn.commit()

c, conn = connect_to_db()
# drop_table(c, conn)
# create_tables(c, conn)

def add_to_traffic_db(c, id, traffic):
    sql = 'INSERT INTO Id_Traffic (id, traffic) VALUES (%s,%s)'
    val = (int(id), int(traffic))
    sql = sql % val
    try:
        c.execute(sql)
        # return c.lastrowid
    except:
        print('Something we wrong: INSERT INTO Id_Traffic ')




def add_to_frist_last(c, id, first, last):
    sql = 'INSERT INTO Id_First_Last (id, first1, last1) VALUES (%s,%s,%s)'
    val = (int(id), '\'' + str(first[0]) + '_' + str(first[1]) + "\'", "\'" + str(last[0]) + '_' + str(last[1]) + "\'")
    sql = sql % val
    try:
        c.execute(sql)
        # return c.lastrowid
    except:
        print('Something we wrong: INSERT INTO Id_First_Last')



def database_commit(conn):
    conn.commit()
database_commit(conn)

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]


# G = nx.karate_club_graph()
nodes = list(G.nodes())

edge_traffic = {}


def initialize_edge_traffic():
    global edge_traffic
    for each in G.edges():
        edge_traffic[each] = 0

initialize_edge_traffic()

def update_edge_traffic(val1, val2, traffic):
    global edge_traffic
    if (val1, val2) in edge_traffic.keys():
        edge_traffic[(val1, val2)] += traffic
    elif (val2, val1) in edge_traffic.keys():
        edge_traffic[(val2, val1)] += traffic
    else:
        print('Poda mone dinesha')
        raise Exception

sub_graph = chunks(nodes, math.ceil(len(nodes)/3))

Mega_graph = [G.subgraph(list(each)) for each in sub_graph]

print('Done Reading')
sd_id = 0
for graph in Mega_graph:
    node_1 = graph.nodes()
    # n = len(list(node_1))
    # n_c_2 = (n*(n-1)/2)
    # node_counter_x = 0
    # graph_id = 0
    for node in node_1:
        # print(node)
        path = nx.single_source_shortest_path(G, node)
        for each in path:
            if each > node:
                # z = n - node
                # id = graph_id*10000 + n_c_2 - (z*(z-1)/2) + each
                # print(id)
                # print(each)
                now = path[each]
                traffic = get_pareto_traffic_one(1, 20)
                add_to_frist_last(c, sd_id, (now[0], now[1]), (now[-2], now[-1]))
                # add_to_traffic_db(c, sd_id, traffic)
                for o in range(len(now) - 1):
                    value = now[o:o + 2]
                    update_edge_traffic(value[0], value[1], traffic)
                sd_id += 1
    # graph_id += 1
    print('One Sub graph done')
    database_commit(conn)

print()