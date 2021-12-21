#!/usr/bin/env python3

import sys
import logging
#To create empty node for parent of start_node to avoid checking for None
from adjlist import AdjacencyList

log = logging.getLogger(__name__)

from math import inf

def warshall(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Warshall's
    algorithm.

    Pre: adjlist is not empty.
    '''
    log.info("TODO: warshall()")
    return [[]]

def floyd(adjlist):
    '''
    Returns an NxN matrix that contains the result of running Floyd's algorithm.

    Pre: adjlist is not empty.
    '''
    log.info("TODO: floyd()")
    return [[]]

def dijkstra(adjlist, start_node):
    '''
    Returns the result of running Dijkstra's algorithm as two N-length lists:
    1) distance d: here, d[i] contains the minimal cost to go from the node
    named `start_node` to the i:th node in the adjacency list.
    2) edges e: here, e[i] contains the node name that the i:th node's shortest
    path originated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: start_node is a member of adjlist.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 2
    b|* * 2
    c|* * *

    For start node "a", the expected output would then be:
    d: [ None, 1, 2]
    e: [ None, 'a', 'a' ]
    '''
    node_list = make_node_list(adjlist)
    node_list[get_node_index(node_list, start_node)].key = 0

    tree = AdjacencyList()
    queue = list(node_list)
    while len(queue) > 0:
        u = extract_min(queue)
        tree = tree_union_node(tree, u)
        for node in node_list:
            if tree.find_edge(u.name(), node.name()):
                dijkstra_relax(u, node)

    d = []
    e = []

    for node in node_list:
        if node.key == 0 or node.key == inf:
            d.append(None)
        else:
            d.append(node.key)
        e.append(node.p.name())

    return d, e

def dijkstra_relax(u, v):
    '''
    Returns true if v.key is changed
    '''
    if v.key > u.key + weight(u, v):
        v.key = u.key + weight(u, v)
        v.p = u
        return True
    return False

def tree_union_node(tree, u):
    if tree.is_empty():
        tree = u
    else:
        u.cons(AdjacencyList())
        tree.cons(u)
    return tree

def prim(adjlist, start_node):
    '''
    Returns the result of running Prim's algorithm as two N-length lists:
    1) lowcost l: here, l[i] contains the weight of the cheapest edge to connect
    the i:th node to the minimal spanning tree that started at `start_node`.
    2) closest c: here, c[i] contains the node name that the i:th node's
    cheapest edge orignated from. 

    If the index i refers to the start node, set the associated values to None.

    Pre: adjlist is setup as an undirected graph and start_node is a member.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 3
    b|1 * 1
    c|3 1 *

    For start node "a", the expected output would then be:

    l: [ None, 1, 1]
    c: [ None, 'a', 'b' ]
    '''
    queue = make_node_list(adjlist)

    
    decrease_key(queue, queue[get_node_index(queue, start_node)], 0)

    all_nodes = list(queue)
    while len(queue) > 0:
        u = extract_min(queue)
        for node in all_nodes:
            if adjlist.find_edge(u.name(), node.name()):
                if node in queue and weight(u, node) < node.key:
                    node.p = u
                    decrease_key(queue, node, weight(u, node))
    
    l = []
    c = []
    for node in all_nodes:
        if node.key != inf and node.key != 0:
            l.append(node.key)
        else:
            l.append(None)
        c.append(node.p.name())

    return l, c

def extract_min(queue):
    smallest = min([node.key for node in queue])
    for node in queue:
        if node.key == smallest:
            temp = node
            queue.remove(node)
            return temp

def decrease_key(queue, node, value):
    if node in queue and value < node.key:
        node.key = value

def weight(src, dst):
    temp = src.edges()
    while not temp.is_empty():
        if temp.dst() == dst.name():
            return temp.weight()
        temp = temp.tail() 

def make_node_list(adjlist):
    queue = list()
    temp = adjlist
    while not temp.is_empty():
        temp.key = inf
        temp.p = AdjacencyList()
        queue.append(temp)
        temp = temp.tail()
    return queue

def get_node_index(adjlist, start_node):
    for i, node in enumerate(adjlist):
        if node.name() == start_node:
            return i

if __name__ == "__main__":
    logging.critical("module contains no main")
    sys.exit(1)
