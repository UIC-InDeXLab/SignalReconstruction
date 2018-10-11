import networkx as nx
import math
from the_traffic_magic import get_pareto_traffic_one
from helper_scratch import chunks, connect_to_db, EdgeNames, graph_open
from dbhelper_scratch import database_commit, get_all_sd_using_this, get_first_last_from_id, add_to_frist_last, add_to_a

c, conn = connect_to_db()

database_commit(conn)

G = nx.karate_club_graph()
# G = graph_open()
print('Done Reading')
nodes = list(G.nodes())

sub_graph = chunks(nodes, math.ceil(len(nodes)/3))
Mega_graph = [G.subgraph(list(each)) for each in sub_graph]

en = EdgeNames(G.edges())

sd_id = 0
total = len(list(G.nodes()))
curr = 0

for node in G.nodes():
    path = nx.single_source_shortest_path(G, node)
    for each in path:
        if each > node:
            now = path[each]
            traffic = get_pareto_traffic_one(1, 20)
            add_to_frist_last(c, sd_id, (now[0], now[1]), (now[-2], now[-1]))
            for o in range(len(now) - 1):
                value = now[o:o + 2]
                add_to_a(c, en.get_edge_id((value[0], value[1])), sd_id)
                en.update_edge_traffic(value[0], value[1], traffic)
            sd_id += 1
    database_commit(conn)
    print(total - curr, ' more nodes.')
    curr += 1

print('Node Exploration Done')
with open('a_db.txt', 'w') as a, open('b_db.txt', 'w') as b:
    for each in en.edge:
        id = en.get_edge_id(each)
        list_all = get_all_sd_using_this(c, id)
        print(list_all)
        # s = ', '.join([str(int(value_1[0])) for value_1 in list_all]) + '\n'
        a.write(', '.join([str(int(value_1[0])) for value_1 in list_all]) + '\n')
        b.write(str(en.get_traffic_on_edge(each)) + '\n')

print("Done writing to a and b")
denom = en.total_traffic()


with open('gravity_db.txt', 'w') as g:
    for i in range(0, int((total*(total-1)/2))):
        l = get_first_last_from_id(c, i)
        first = l[0][0].split('_')
        # first = en.get_traffic_on_edge((int(first[0]), int(first[1])))
        last = l[0][1].split('_')
        # last = en.get_traffic_on_edge((int(last[0]), int(last[1])))
        g.write(str(en.get_traffic_on_edge((int(first[0]), int(first[1])))*en.get_traffic_on_edge((int(last[0]), int(last[1])))/denom) + '\n')


print("Done writing to gravity")

print()


