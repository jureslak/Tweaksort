import matplotlib.pyplot as plt 
from sys import argv
from os.path import exists
from collections import deque

settings = [
        dict(c="b", edgecolors="b", marker="o"),
        dict(c="r", edgecolors="r", marker="x"),
        dict(c="g", edgecolors="g", marker="s"),
        dict(c="#FF8000", edgecolors="#FF8000", marker="d")
        ]

if len(argv) < 2:
    print "Which file should be read?"
elif len(argv) > 5:
    print "Too many args!"
else:
    i = 0
    ax, ay = [[],[]], [[],[]]
    leg = []
    for arg in argv[1:]:
        x,y = [], []
        if exists(arg):
            f = open(arg, 'r')
            a = f.readline() #first line
            a = f.readline().strip()
            while a != "Done!":
                a = a.split()
                x.append(float(a[0]))
                y.append(float(a[1]))
                a = f.readline().strip()
            ax[0].append(max(x))
            ay[0].append(max(y))
            ax[1].append(min(x))
            ay[1].append(min(y))
            leg.append(arg)
            f.close()
            plt.scatter(x, y, **settings[i])
        else:
            print "File not found", arg
        i += 1
    plt.axis([min(ax[1]), max(ax[0]), min(ay[1]), max(ay[0])])
    leg = deque(leg)
    leg.rotate(-1)
    plt.legend(leg, "right")
    plt.show() 
