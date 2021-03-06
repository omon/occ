#! /usr/bin/env python
import os
import shutil
import subprocess
import sys

def test(expected, input):
    shutil.copyfile('cmake-build-debug/occ', 'occ')
    os.chmod('occ', 777)
    os.system('./occ {0}'.format(input))
    os.system('gcc --static -o tmp tmp.s')
    result = subprocess.run('./tmp')
    ret = result.returncode
    if ret == expected:
        print('{0} => {1}'.format(input , expected)) 
    else:
        print('{0} expected but not {1}'.format(input, ret))
        print(' ==== NG ==========')
        sys.exit(1)
    return True

if __name__ == '__main__':
    test(0, '0')
    test(42, '42')
    test(21, '5+20-4')
    test(41, '"12 + 34 - 5"')
    test(153, '"1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17"')
    print('OK')

    
