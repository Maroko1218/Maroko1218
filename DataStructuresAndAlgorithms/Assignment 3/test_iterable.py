from adjlist import AdjacencyList
from math import inf

def print_adjmatrix(adjlist):
    """ This won't work until you've implemented adjacency_matrix """
    print(" ".join("{:^3}".format(name) for name in adjlist.list_nodes()))
    for row in adjlist.adjacency_matrix():
        print(" ".join(" * " if val is inf else "{:^3}".format(val) for val in row)) # This is a type of list comprehension

def print_adjlist(adjlist):
    """ Note how I can use "for x in y" syntax to loop through my nodes and edges now """
    for node in adjlist:
        print("{}: ".format(node.head().name()), end="")
        # join is a handy string method which creates a single string from a sequency of strings, by putting the original
        # string (in this case " -> ") between each string in the sequence (which is being generated in-line by the for loop)
        print(" -> ".join("({}, {})".format(edge.dst(), edge.weight()) for edge in node.head().edges())) # This is a type of list comprehension

if __name__ == "__main__":
    # Creates the graph from the example in the lab specification
    g = AdjacencyList()
    g = g.add_node("a")
    g = g.add_node("b")
    g = g.add_node("c")

    g = g.add_edge("a", "b", 1)
    g = g.add_edge("a", "c", 2)
    g = g.add_edge("b", "c", 2)
    g = g.add_edge("c", "b", 1)

    print_adjmatrix(g)
    print()
    print_adjlist(g)
    print()

