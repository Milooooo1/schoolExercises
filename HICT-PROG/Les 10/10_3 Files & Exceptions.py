running = True
while running:
    filename = input("Voer de naam van het bestand in: ")
    try:
        infile = open(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 6"+"\\"+filename+".txt","r")
        running = False
    except FileNotFoundError:
        print("De ingevulde naam is niet correct, probeer het opnieuw.")

lineList = infile.readlines()
print("Dit bestand heeft", len(lineList), "regels.")
kaartnummers = [i[0:6] for i in lineList]
kaartnummers = list(map(int, kaartnummers))
regelnummers = kaartnummers
kaartnummers.sort()
print("Het grootste kaartnummer is:", kaartnummers[-1], "en die staat op regel", regelnummers.index(kaartnummers[-1]) - 1)