#GiG

import igraph
from scipy.sparse import dok_matrix, lil_matrix
import numpy as np
import pandas as pd
from the_traffic_magic import get_pareto_traffic_one

def write_A_matrix(graph_file_name, A_matrix_file_name, b_vector_file_name, gravity_vector_file_name):
    #Do bulk read - much efficient
    graph = igraph.Graph.Read(graph_file_name, format = "edgelist", directed=False)

    output_file = open(A_matrix_file_name, "w")

    #Read uses a 0 based index - so if using 1 based index be careful about indices
    start_node = 0 #in case you want to do a dumb parallelization set these values
    end_node = graph.vcount() #ditto

    s_d_pair_index = 0

    #create a fake attribute to store all sd_paths this edge participates in.
    # Igraph does not allow empty sequences - so put a sentinel and remove it later
    graph.es["sd_pairs"] = ""
    graph.es["edge_traffic"] = "0"
    graph.vs["sd_id_source_destination"] = ""

    total_traffic = 0

    #xrange does not create the list
    for node in range(start_node, end_node):
        paths = graph.get_shortest_paths(node, mode=igraph.OUT,output='vpath')
        #ignore unreachable nodes and self loops of length 1
        paths = [path for path in paths if len(path) > 1]
        for path in paths:
            traffic = get_pareto_traffic_one(1, 20)
            total_traffic += traffic
            s_d_pair_index_as_str = str(s_d_pair_index)
            for edge_src, edge_target in zip(path[:-1], path[1:]):
                graph.es[graph.get_eid(edge_src, edge_target)]["sd_pairs"] += s_d_pair_index_as_str + ","
                graph.es[graph.get_eid(edge_src, edge_target)]["edge_traffic"] = str(int(graph.es[graph.get_eid(edge_src, edge_target)]["edge_traffic"])+traffic)
            s_d_pair_index += 1
            f = graph.get_eid(path[0], path[1])
            l = graph.get_eid(path[-2], path[-1])
            f_l = s_d_pair_index_as_str + '_' + str(f) + '_' + str(l)
            graph.vs[node]["sd_id_source_destination"] += f_l + ","

    output_file.write(str(graph.ecount()) + "," + str(s_d_pair_index - 1) + "\n")

    b_file = open(b_vector_file_name, "w")

    for edge in graph.es:
        output_file.write(edge["sd_pairs"][:-1] + "\n")
        b_file.write(edge["edge_traffic"] + "\n")
    output_file.close()
    b_file.close()

    output_file_gravity = open(gravity_vector_file_name, "w")
    for node in graph.vs:
        for each in node["sd_id_source_destination"].split(','):
            each = each.split('_')
            output_file_gravity.write(str(each[0]) + ' ' + str((int(graph.es[int(each[1])]["edge_traffic"])*int(graph.es[int(each[2])]["edge_traffic"]))/total_traffic))
    output_file_gravity.close()
#write_A_matrix("test.txt", "temp.csv")
write_A_matrix("p2p-Gnutella04_Nodes_10876_edges_39994.txt", "jees_pd_output.csv", 'jees_pd_b.csv','gravity_vector_file_name.csv')
#write_A_matrix("p2p-Gnutella04_Nodes_10876_edges_39994.txt", "gnutella_A_matrix.csv")
