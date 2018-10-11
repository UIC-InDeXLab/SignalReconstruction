

__author__ = "Jees Augustine, Azade Nazi, Abolfazl and Gautam Das"
__copyright__ = "Copyright 2016, The **** Project"
__credits__ = ["Jees Augustine", "Azade Nazi", "Gautam Das"]
__license__ = "GPL"
__version__ = "1.0.0"
__maintainer__ = "Jees Augustine"
__email__ = "jees.augustine@mavs.uta.edu"
__status__ = "Research"
import math
import random


def get_pareto_traffic(alpha, xm, sample_size, sys_path, write_to_file):
    import math
    import random

    distribution = []
    val = []

    for each in range(int(sample_size)):
        for_this = random.random()
        x = (xm / math.pow((1 - for_this), (1 / alpha)))
        val.append(for_this)
        distribution.append(math.ceil(x))

    if write_to_file:
        write_traffic_to_file_here(sys_path + '/Input_Traffic/traffic_distribution.txt',sample_size, distribution)

    return distribution


def get_pareto_traffic_one(alpha, xm, sample_size=None, sys_path=None, write_to_file=None):
    for_this = random.random()
    return math.ceil(xm / math.pow((1 - for_this), (1 / alpha)))


def write_traffic_to_file_here(filename, total_src_destination_pairs, traffic):
    import math
    i = 0
    with open(filename, 'w') as the_file:
        for each in range(total_src_destination_pairs):
            the_file.write(str(math.ceil(traffic[each])) + '\n')
