#! /usr/bin/python2.7

"""
Your Name
Lab 11
Physics 91SI, Spring 2013
"""

import sys

def main():
    """Join command-line arguments and pass them to unitcalc(), then print."""
    calculation = ''.join(sys.argv[1:])
    print unitcalc(calculation)

def unitcalc(s):
    """Parse a string describing an operation on quantities with units."""

    # TODO make this robust for differently formatted inputs
    num1 = s[0]
    num2 = s[2]
    operation = s[1]

    if operation=='+':
        return int(num1)+int(num2)
    elif operation=='-':
        pass
    elif operation=='*':
        pass
    elif operation=='*':
        pass


if __name__ == "__main__": main()
