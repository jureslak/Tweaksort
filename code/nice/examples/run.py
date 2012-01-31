import os

import argparse

def stype(string):
    if string not in ["int", "string", "huge", "slow"]:
        raise argparse.ArgumentTypeError("type not one of %s %s!" % ('int', 'string'))
    return string

def ssort(string):
    if string not in ["s", "q", "i", "t", "c", "h", "m"]:
        raise argparse.ArgumentTypeError("type not one of sorts!")
    return string

def ssep(string):
    if string not in ["type", "sort", "none"]:
        raise argparse.ArgumentTypeError("sep not one of type sort none!")
    return string


parser = argparse.ArgumentParser(prog='python run.py', description='Runs requested sorts on requested types.')
parser.add_argument('L', default=0, type=int,  help='lower bound', nargs='?')
parser.add_argument('M', type=int,  help='upper bound')
parser.add_argument('step', default=1, type=int,  help='step', nargs='?')
parser.add_argument('iter', default=1, type=int,  help='iterations', nargs='?')
parser.add_argument('limit', default=-1, type=int,  help='how many elements in memory',
        nargs='?')

parser.add_argument('-t', '--types', dest='types', nargs='+', type=stype,
        default=["int"], help='which type of data to show')
parser.add_argument('-s', '--sorts', dest='sorts', nargs='*', type=ssort,  help='which sorts to show (+s or -s) \
where s one of "q m c h i t s". If all -s, they are substracted from all. All is deafult')
parser.add_argument('--sep', dest='sep', nargs='?', type=ssep, default="type", 
help='new plot for each "sort" or for "type" or all at once ("none")')

args = parser.parse_args()

if args.sorts == None or args.sorts == []:
    sorts = ["q", "i", "c", "h", "m", "t", "s"]
else:
    sorts = list(set(args.sorts)) # remove duplicates

sortargs = ' '.join(sorts)
typeargs = ' '.join(args.types)

def targ(arr):
    a = [0 for x in range(4)]
    a[0] = '1' if "int" in arr else '0'
    a[1] = '1' if "string" in arr else '0'
    a[2] = '1' if "huge" in arr else '0'
    a[3] = '1' if "slow" in arr else '0'
    return ''.join(a)

if args.limit == -1:
    args.limit = (args.M) * args.iter

if args.sep == "type":
    command = ["./test %d %d %d %d %d %s > out; python plot.py -t %s -s %s < out" % (args.L, args.M,
            args.step, args.iter, args.limit, targ([t]), t, sortargs) for t in args.types]
    for com in command:
        os.system(com)

elif args.sep == "sort":
    command = ["./test %d %d %d %d %d %s > out; python plot.py -t %s -s %s < out" % (args.L, args.M,
            args.step, args.iter, args.limit, targ(args.types), typeargs, s) for s in sorts]
    for com in command:
        os.system(com)
elif args.sep == "none":
    os.system("./test %d %d %d %d %d %s > out | python plot.py -t %s -s %s < out" % (args.L, args.M,
        args.step, args.iter, args.limit, targs(args.types), typeargs, sortargs))
