#Opdracht 6_2 Files lezen
infile = open("kaartnummers.txt", "r+")
lineList = infile.readlines()
for name in lineList:
    f1 = name.split()
    if len(f1) == 3:
        print(f1[1], f1[2], "heeft kaarnummer:", f1[0])
    else:
        print(f1[1], f1[2], f1[3], "heeft kaartnummer:", f1[0])