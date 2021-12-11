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
        return temp.balance()

    def delete(self, v):
        temp = bst.BST.delete(self, v)
        return temp.balance()

    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
        if self.lc().height() - self.rc().height() >= 2:
            if self.lc().lc().height() >= self.lc().rc().height():
                return self.srr()
            else:
                return self.drr()
        elif self.lc().height() - self.rc().height() <= -2:
            if self.rc().rc().height() >= self.rc().lc().height():
                return self.slr()
            else:
                return self.dlr()
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
        self.set_rc(self.rc().srr())
        return self.slr()

    def drr(self):
        '''
        Performs a double-right rotate around the node rooted at `self`.
        '''
        self.set_lc(self.lc().slr())
        return self.srr()

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
