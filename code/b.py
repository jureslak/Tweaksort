import sys

for i in sys.stdin:
    if "false" in i:
        print i
