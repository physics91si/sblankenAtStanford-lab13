import unittest
import unitcalc as uc

class MyTest(unittest.TestCase):
    # TODO implement tests here to verify that your functions work!
    def testAddition(self):
        self.assertEqual(uc.unitcalc('1+1'),2)

    def testSubtraction(self):
        pass

    def testMultiplciation(self):
        pass
    def testDivision(self):
       pass

if __name__ == '__main__':
    unittest.main()

