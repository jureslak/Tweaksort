import argparse

def sstring(string):
    if string not in ["int", "string", "huge", "slow"]:
        raise argparse.ArgumentTypeError("type not one of %s %s!" % ('int', 'string',
        'huge', 'slow'))
    return string

def ssort(string):
    if string not in ["+q", "+i", "+c", "+h", "+m", "+t", '-q', '-i', '-t', '-m', '-h',
            '-c', '-s', '+s', '-b', '+b']:
        raise argparse.ArgumentTypeError("type not one of sorts!")
    return string

parser = argparse.ArgumentParser(description='Draws plot of sorts and datatypes given via stdandard input.')
parser.add_argument('-t', '--type', dest='type', nargs='+', type=sstring, help='which type of data to show')
parser.add_argument('-s', '--sorts', dest='sorts', nargs='*', type=ssort,  help='which sorts to show (+s or -s) \
where s one of "q m c h i t s". If all -s, they are substracted from all. All is deafult')
args = parser.parse_args()

if args.sorts == None: args.sorts = []
args.sorts = list(set(args.sorts)) # remove duplicates
sorts = set(["q", "i", "c", "h", "m", "t", "s", 'b'])
for i in args.sorts:
    if i[0] == '+':
        sorts = set(); break

minus = set()
plus = set()
for i in args.sorts:
    if i[0] == '-': minus.add(i[1])
    elif i[0] == '+': plus.add(i[1])

sorts |= plus
sorts -= minus


leg = []; j = 0;
x = [[] for i in range(len(sorts))]
y = [[] for i in range(len(sorts))]
while True:
    a = raw_input();
    if a == "Done!": break
    if a[:4] == "ln: ":
        M = int(a[4:])
        k = 0
        for i in range(8):
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
                    leg.append(a[0])
                k += 1 
    j+=1

out = [' '] + leg
for j in range(len(x[0])):
    for i in range(len(out)):
        if i == 0:
            out[i] += " & " + str(x[i][j])
        else:
            out[i] += " & " + str(y[i - 1][j])

out = ' \\\\ \\hline \n  '.join(out)
out = "\\begin{tabular}{|" + '|'.join(["l" for x in range(len(x[0]) + 1)]) + "|}\n  \\hline\n" +\
out + "\\\\ \\hline \n\\end{tabular}"
print out
