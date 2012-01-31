from pypsum import get_lipsum
import argparse

def sstring(string):
    if string not in ["words", "bytes", "paragraphs", "lists"]:
        raise argparse.ArgumentTypeError("type not one of 'words', 'paragraphs', 'lists', 'bytes'!")
    return string

parser = argparse.ArgumentParser(description='Process integer and writes random words to rtext.txt.')
parser.add_argument('integer', metavar='N', type=int,  help='an integer for the accumulator')
parser.add_argument('type_of_content', type=sstring, help='an integer for the accumulator')
parser.add_argument('-l', '--lorem', dest='lorem', action='store_true', default=False, help='start with lorem ipsum ...')
parser.add_argument('-f', '--file', dest='file', default="rtext.txt", help='start with lorem ipsum ...')
args = parser.parse_args()

print "Starting ..."
f = open(args.file, 'w');
f.write('\n'.join((get_lipsum(args.integer, args.type_of_content, "yes" if args.lorem else "no")[0]).split()))
f.close()
print "Done!" 
