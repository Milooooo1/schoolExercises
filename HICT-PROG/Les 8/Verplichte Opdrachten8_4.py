#Opdracht 8_4 File & Dict
def ticker():
    bedrijven = open(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 8\bedrijven.txt", "r+")
    bedrijf = bedrijven.readlines()
    bedrijfEnSymbool = []
    for naam in bedrijf:
        b1 = naam.split(":")
        bedrijfEnSymbool.append(b1)
    d = {}
    for elem in bedrijfEnSymbool:
        try:
            d[elem[0]].append(elem[1])
        except KeyError:
            d[elem[0]] = [elem[1]]
    bedrijven.close()
    return(d)

bedrijfNaam = list(ticker().keys())
bedrijfSymbool = list(ticker().values())
flattenedBedrijfSymbool = []
for x in bedrijfSymbool:
    for y in x:
        flattenedBedrijfSymbool.append(y[:-1])
print(bedrijfNaam)
print(flattenedBedrijfSymbool)
keuze = int(input("Wilt u een bedrijf of ticker symbool invullen? Bedrijf = 0, Ticker Symbool = 1 "))
if keuze == 1:
    invoerTickerSymbool = str(input("Vul het ticker symbool in: "))
    print(flattenedBedrijfSymbool)
    print(invoerTickerSymbool)
    inLijst = invoerTickerSymbool in flattenedBedrijfSymbool
    if inLijst == True:
        print("Bedrijfsnaam: ", str(bedrijfNaam[flattenedBedrijfSymbool.index(str(invoerTickerSymbool))]))
    else:
        print("Het opgegeven symbool wordt niet herkent.")
elif keuze == 0:
    invoerBedrijfNaam = str(input("Vul de naam van het bedrijf in: "))
    print("Ticker Symbool:",flattenedBedrijfSymbool[(bedrijfNaam.index(invoerBedrijfNaam))])
