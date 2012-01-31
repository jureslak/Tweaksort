f = [x.strip().split(":") for x in open(raw_input("Filename: "), 'r') if x.strip()[-2:] != "-1"]

# find all sorts and type
first_len = f[0][1]
cur_len = first_len
type_name = f[1][0][1]

a = dict()

for i in f:
    if i[0] == "ln":
        cur_len = i[1]
    elif i[0] == "Done!":
        break;
    else:
        if i[0][0] not in a:
            a[i[0][0]] = float(i[1])
        else:
            a[i[0][0]] += float(i[1])

a = [x + ": " + str(a[x]) for x in a]
a.sort(key=lambda x: float(x[3:]))

print "type: %s" % type_name
print "first: %s" % first_len
print "last: %s" % cur_len

for i in a:
    print i
