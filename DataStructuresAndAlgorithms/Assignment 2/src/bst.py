#!/usr/bin/env python3

import bt
import sys
import logging

log = logging.getLogger(__name__)

class BST(bt.BT):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(BST(), BST())

    def is_member(self, v):
        '''
        Returns true if the value `v` is a member of the tree.
        '''
        #logging.info("TODO@src/bst.py: implement is_member()")
        return v in self.inorder()

    def size(self):
        '''
        Returns the number of nodes in the tree.
        '''
        #logging.info("TODO@src/bst.py: implement size()")
        if not self.lc().is_empty() and not self.rc().is_empty():
            return self.lc().size() + self.rc().size() + 1
        elif not self.lc().is_empty():
            return self.lc().size() + 1
        elif not self.rc().is_empty():
            return self.rc().size() + 1
        return 1
        

    def height(self):
        '''
        Returns the height of the tree.
        '''
        #logging.info("TODO@src/bst.py: implement height()")
        if not self.lc().is_empty() and not self.rc().is_empty():
            return max(self.lc().height(), self.rc().height()) + 1
        elif not self.lc().is_empty():
            return self.lc().height() + 1
        elif not self.rc().is_empty():
            return self.rc().height() + 1
        return 1
        
    def preorder(self):
        '''
        Returns a list of all members in preorder.
        '''
        if self.is_empty():
            return []
        return [self.value()] + self.lc().preorder() + self.rc().preorder()

    def inorder(self):
        '''
        Returns a list of all members in inorder.
        '''
        #log.info("TODO@src/bst.py: implement inorder()")
        if self.is_empty():
            return []
        return self.lc().inorder() + [self.value()] + self.rc().inorder() 

    def postorder(self):
        '''
        Returns a list of all members in postorder.
        '''
        #log.info("TODO@src/bst.py: implement postorder()")
        if self.is_empty():
            return []
        return self.lc().postorder() + self.rc().postorder() + [self.value()]

    def bfs_order_star(self):
        '''
        Returns a list of all members in breadth-first search* order, which
        means that empty nodes are denoted by "stars" (here the value None).

        For example, consider the following tree `t`:
                    10
              5           15
           *     *     *     20
                           *    25

        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        '''
        output = list()
        if not self.is_empty():
            queue = list()
            queue.append(self)
            length = (2 ** self.height()) - 1
            i = 0
            scounter = 0
            while queue != [] and i < length:
                p = queue[0]
                queue.remove(p)
                if not p.is_empty():
                    scounter += 1
                output.append(p.value())
                if not p.is_empty() and p.height() > 1:
                    if not p.lc().is_empty():
                        queue.append(p.lc())
                    elif scounter < self.size():
                        queue.append(BST())
                    if not p.rc().is_empty():
                        queue.append(p.rc())
                    elif scounter < self.size():
                        queue.append(BST())
                i += 1

        return output

        #log.info("TODO@src/bst.py: implement bfs_order_star()")

    def add(self, v):
        '''
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        '''
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v < self.value():
            return self.cons(self.lc().add(v), self.rc())
        if v > self.value():
            return self.cons(self.lc(), self.rc().add(v))
        return self
    
    def delete(self, v):
        '''
        Removes the value `v` from the tree and returns the new (updated) tree.
        If `v` is a non-member, the same tree is returned without modification.
        '''
        log.info("TODO@src/bst.py: implement delete()")
        return self

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
