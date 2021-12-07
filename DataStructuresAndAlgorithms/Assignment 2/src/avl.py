#!/usr/bin/env python3

#Markus Svan och Jesper Olsson
import bst
import sys
import logging

log = logging.getLogger(__name__)

class AVL(bst.BST):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(AVL(), AVL())

    def add(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        log.debug("calling bst.BST.add() explicitly from child")
        temp = bst.BST.add(self, v)
        self.balance() # TODO: apply this method correctly for add/delete
        return temp
    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
        log.info("TODO@src/avl.py: implement balance()")
        self.slr().srr().dlr().drr() # TODO: apply these methods correctly
        return self

    def slr(self):
        '''
        Performs a single-left rotate around the node rooted at `self`.
        '''
        temprc = self.rc()
        self.set_rc(temprc.lc())
        temprc.set_lc(self)
        return temprc

    def srr(self):
        '''
        Performs a single-right rotate around the node rooted at `self`.
        '''
        templc = self.lc()
        self.set_lc(templc.rc())
        templc.set_rc(self)
        return templc

    def dlr(self):
        '''
        Performs a double-left rotate around the node rooted at `self`.
        '''
        self.set_rc(self.lc().srr())
        return self.slr()

    def drr(self):
        '''
        Performs a double-right rotate around the node rooted at `self`.
        '''
        self.set_lc(self.rc().slr())
        return self.srr()

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
