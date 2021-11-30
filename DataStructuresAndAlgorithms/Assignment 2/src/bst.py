#!/usr/bin/env python3

#Markus Svan och Jesper Olsson
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
        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        '''
        output = list()
        if not self.is_empty():
            queue = list()
            queue.append(self)
            length = (2 ** self.height()) - 1
            i = 0
            while queue != [] and i < length:
                p = queue[0]
                queue.remove(p)
                output.append(p.value())
                if not p.is_empty():
                    if not p.lc().is_empty():
                        queue.append(p.lc())
                    else:
                        queue.append(BST())
                    if not p.rc().is_empty():
                        queue.append(p.rc())
                    else:
                        queue.append(BST())
                else:
                    queue.append(BST())
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
        if self.is_empty():
            return self #returns the empty tree
        if not self.is_member(v):
            return self #returns the tree as it is when v isnt in tree
        if v < self.value():
            return self.cons(self.lc().delete(v),self.rc())
        if v > self.value():
            return self.cons(self.lc(), self.rc().delete(v))
        return self.remove_root()
        #log.info("TODO@src/bst.py: implement delete()")
        return self

    def remove_root(self):
        if self.is_leaf(): #if leaf node
            self.set_value(None)
            self.set_lc(None)
            self.set_rc(None)
        elif not self.lc().is_empty() and self.rc().is_empty(): #if node has left child 
            self.set_value(self.lc().value())
            self.set_rc(self.lc().rc())
            self.set_lc(self.lc().lc()) 
        elif self.lc().is_empty() and not self.rc().is_empty(): #if node has right child
            self.set_value(self.rc().value())
            self.set_lc(self.rc().lc())
            self.set_rc(self.rc().rc())
        elif not self.lc().is_empty() and not self.rc().is_empty(): #if node has left and right child
            if self.lc().height() > self.rc().height(): #not sure if this works. balance depending on which child has the largest depth
                biggest = max(self.lc().inorder())
                self.delete(biggest)
                self.set_value(biggest)
            else:
                lowest = min(self.rc().inorder())
                self.delete(lowest)
                self.set_value(lowest)
                #find and take lowest value node from the right subtree and replace local root with it
        return self


if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
