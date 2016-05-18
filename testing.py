#!/usr/bin/python

# Lab 13
# Physics 91SI
# Spring 2016

import unittest
import calc

class CalcTest(unittest.TestCase):
    # TODO implement tests here to verify that your functions work!
    def testAddition(self):
        self.assertEqual(calc.calc('10+1'), 11)

    def testSubtraction(self):
        self.assertEqual(calc.calc('10-8'), 2)

    def testMultiplciation(self):
        self.assertEqual(calc.calc('3*1'), 3)
 
    def testDivision(self):
        self.assertEqual(calc.calc('8/2'), 4)

if __name__ == '__main__':
    unittest.main()

