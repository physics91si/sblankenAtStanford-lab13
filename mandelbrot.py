#!/usr/bin/python2.7

import sys
import numpy as np
from scipy import weave

# For timing
import time

# Test scipy.weave vs. Python for computing the Mandlebrot set
# Physics 91SI, Spring 2013
# Lab #14, Part 1

def weave_test(grid, nmax):
    ### Weave C++ code for testing a point for Mandelbrot set membership
    # c : point to test
    # nmax : max iterations
    code = r"""
        std::complex<double> z = std::complex<double>(0,0);
        return_val = 0;
        // weave convention; store your return value in this variable
        
        /*
         * Your C++ code goes here
         */
        """

    retgrid = np.zeros(grid.shape)
    for (a,b), c in np.ndenumerate(grid):
        # Call our weave code, passing values for c and nmax
        retgrid[a,b] = weave.inline(code, ['c', 'nmax'],
                                    headers=['<math.h>', '<complex>'])
    return retgrid


def python_test(grid, nmax):
    """Compute the Mandelbrot set for the given grid of complex numbers."""

    # Python allows nested function definitions
    def test_mandelbrot(c, nmax):
        """Test for membership in Mandelbrot set, using pure Python. Returns 0
        if in set, otherwise returns number of iterations needed to escape"""
        i = 0
        z = 0+0j
        while i < nmax:
            # If either component is greater than 2, the point will escape to
            # infinity

            if abs(z.real) >= 2 or abs(z.imag) >= 2:
                return i
            z = z**2 + c # Iterate the mapping
            i += 1;
        return 0

    retgrid = np.zeros(grid.shape)
    for (a,b), c in np.ndenumerate(grid):
        retgrid[a,b] = test_mandelbrot(c, nmax)
    return retgrid


def plot_mandelbrot(grid, rlim, ilim):
    from matplotlib import pyplot as plt
    plt.ion()
    grid = 1 - np.exp(-grid/25.0)
    plt.imshow(grid, extent=(rlim[0], rlim[1], ilim[0], ilim[1]))
    plt.xlabel("Re(z)")
    plt.ylabel("Im(z)")
    plt.title("Mandelbrot Set")


def print_usage():
    name = sys.argv[0]
    print "Usage: %s -flags [ngrid] [nmax]" % name
    print "-p    : use pure Python"
    print "-w    : use scipy.weave"
    print "-h    : print this message (help)"


def main():
    nmax = 200 # Maximum iterations
    ngrid = 400 # Resolution to compute

    flags = sys.argv[1]
    if 'h' in flags: print_usage()
    
    try: ngrid = int(sys.argv[2])
    except: print "Using default ngrid=%d" % ngrid

    try: nmax = int(sys.argv[3])
    except: print "Using default nmax=%d" % nmax

    # Range of values to compute
    rlim = (-2, 1, ngrid)
    ilim = (-1.5, 1.5, ngrid)

    # Generate grid
    reals = np.linspace(*rlim)
    imags = 1j*np.linspace(*ilim)
    rr, ii = np.meshgrid(reals, imags)
    grid = rr + ii

    t0 = time.time()

    if 'w' in flags:
        print "Testing with scipy.weave..."
        retgrid = weave_test(grid, nmax)

    if 'p' in flags:
        print "Testing with Python..."
        retgrid = python_test(grid, nmax)

    print "Executed in %f seconds" % (time.time() - t0)

    plot_mandelbrot(retgrid, rlim[0:2], ilim[0:2])

    # Comment this out if using iPython, or UNIX time command
    ans = raw_input("Press Enter to exit...")

if __name__ == '__main__':
    main()
