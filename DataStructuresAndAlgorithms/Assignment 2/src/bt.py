#!/usr/bin/env python3

import sys
import logging

log = logging.getLogger(__name__)

class BT:
    _value = None
    _left_child = None
    _right_child = None

    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(BT(), BT())

    def cons(self, lc, rc):
        '''
        Constructs a tree rooted at `self` based on new left/right children.
        '''
        self.set_lc(lc)
        self.set_rc(rc)
        return self

    def is_empty(self):
        '''
        Returns true if the tree is empty.
        '''
        return self.value() is None

    def lc(self):
        '''
        Returns a reference to the left child.
        '''
        return self._left_child

    def rc(self):
        '''
        Returns a reference to the right child.
        '''
        return self._right_child

    def value(self):
        '''
        Returns the value of the node rooted as `self`.
        '''
        return self._value

    def set_value(self, value):
        '''
        Sets the value rooted at `self`.
        '''
        self._value = value
        return self

    def set_lc(self, left_child):
        '''
        Sets the left child.
        '''
        self._left_child = left_child
        return self

    def set_rc(self, right_child):
        '''
        Sets the right child
        '''
        self._right_child = right_child
        return self

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
