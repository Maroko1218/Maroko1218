# Add this method to AdjacencyList
def __iter__(self):
    return AdjacencyListIterator(self.head())

# Add this method to Edge
def __iter__(self):
    return EdgeIterator(self.head())


# Add these classes to the end of the file (but before if __name__ == "__main__" part)
# Actually doesn't really matter where you add them (as long as you don't add them inside another class)
# but thought adding them after the AdjacencyList and Edge classes made more sense

class AdjacencyListIterator:
    """Example of implementing an iterator for a linked list in python"""
    def __init__(self, start):
        self._current = start

    def __iter__(self):
        return self

    def __next__(self):
        node = self._current
        if node.is_empty():
            raise StopIteration
        self._current = node.tail()
        return node

class EdgeIterator:
    def __init__(self, start):
        self._current = start

    def __iter__(self):
        return self

    def __next__(self):
        edge = self._current
        if edge.is_empty():
            raise StopIteration
        self._current = edge.tail()
        return edge
