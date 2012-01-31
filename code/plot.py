import matplotlib.pyplot as plt 
from collections import deque

import argparse

def sstring(string):
    if string not in ["int", "string", "huge", "slow"]:
        raise argparse.ArgumentTypeError("type not one of %s %s!" % ('int', 'string',
        'huge', 'slow'))
    return string

def ssort(string):
    if string not in ["q", "i", "s", "t", "h", "m", "c"]:
        raise argparse.ArgumentTypeError("type not one of sorts!")
    return string

parser = argparse.ArgumentParser(description='Draws plot of sorts and datatypes given via stdandard input.')
parser.add_argument('-t', '--type', dest='type', nargs='+', type=sstring, help='which type of data to show')
parser.add_argument('-s', '--sorts', dest='sorts', nargs='*', type=ssort,  help='which sort s to show \
where s one of "q m c h i t s". All is deafult')
args = parser.parse_args()


settings = [
        dict(c="r"       , markeredgecolor="r"       , marker="x") , 
        dict(c="#000000" , markeredgecolor="#000000" , marker="*") , 
        dict(c="g"       , markeredgecolor="g"       , marker="s") , 
        dict(c="#FF8000" , markeredgecolor="#FF8000" , marker="d") , 
        dict(c="#00FFFF" , markeredgecolor="#00FFFF" , marker="+") , 
        dict(c="#FF00FF" , markeredgecolor="#FF00FF" , marker="2") , 
        dict(c="b"       , markeredgecolor="b"       , marker="o") , 
]

conv = dict(
        t="s konfiguracijo",
        m="z zlivanjem",
        q="hitro urejanje",
        i="z vstavljanjem",
        s="z izbiranjem",
        h="s kopico",
        c="C++ algoritem"
        )


if args.sorts == None or args.sorts == []: 
    sorts = set(["q", "i", "c", "h", "m", "t", "s"])
else:
    sorts = set(args.sorts) # remove duplicates

leg = []; j = 0;
x = [[] for i in range(len(sorts))]
y = [[] for i in range(len(sorts))]
while True:
    a = raw_input();
    if a == "Done!": break
    if a[:4] == "ln: ":
        M = int(a[4:])
        k = 0
        for i in range(7):
            a, b, c, d = raw_input(), raw_input(), raw_input(), raw_input()
            if a[0] in sorts:
                if "int" in args.type:
                    x[k].append(M)
                    y[k].append(float(a[4:]))
                if "string" in args.type:
                    x[k].append(M)
                    y[k].append(float(b[4:]))
                if "huge" in args.type:
                    x[k].append(M)
                    y[k].append(float(c[4:]))
                if "slow" in args.type:
                    x[k].append(M)
                    y[k].append(float(d[4:]))
                if j == 0:
                    leg.append(conv[a[0]])
                k += 1
    j+=1


plots = [plt.plot(x[i], y[i], label=leg[i], **settings[i]) for i in range(len(sorts)) ]
xmin = 0;
xmax = max(max(f) for f in x);
ymin = 0;
ymax = max(max(f) for f in y);
plt.axis([xmin, xmax, ymin, ymax])

#leg = deque(leg)
#leg.rotate(-1)

plt.legend(plots, leg, "upper left")
plt.xlabel("n", x=0.95, horizontalalignment="right");
plt.ylabel("t [ns]", y=0.95, verticalalignment="top", rotation="horizontal");

#plt.title("tip: " + ' '.join(args.type), weight="roman")
#plt.legend(leg, "center left")
plt.show() 
