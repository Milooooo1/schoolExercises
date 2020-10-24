#Opdracht 6_3 Files lezen
infile = open(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 6\kaartnummers.txt","r")
lineList = infile.readlines()
print("Dit bestand heeft", len(lineList), "regels.")
kaartnummers = [i[0:6] for i in lineList]
kaartnummers = list(map(int, kaartnummers))
regelnummers = kaartnummers
kaartnummers.sort()
print("Het grootste kaartnummer is:", kaartnummers[-1], "en die staat op regel", regelnummers.index(kaartnummers[-1]) - 1)