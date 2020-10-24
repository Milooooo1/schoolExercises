def inlezen_beginstations(stations):
    running = True
    while running:
        beginstation = input("Wat is uw beginstation? ")
        if beginstation.lower() in stations:
            print("Station geselecteerd \n")
            running = False
        else:
            print("Dit is geen geldig station probeer het opnieuw.")
    return beginstation

def inlezen_eindstations(stations, beginstation):
    running = True
    while running:
        eindstation = input("Wat is uw eindstation? ")
        try:
            if beginstation.lower() in stations and stations.index(eindstation) > stations.index(beginstation):
                print("Station geselecteerd \n")
                running = False
            else:
                print("Dit is geen geldig station probeer het opnieuw.")
        except ValueError:
            print("Dit is geen geldig station")
    return eindstation

def omroepen_reis(stations, beginstation, eindstation):
    rangnummerBeginstation = stations.index(beginstation) + 1
    rangnummerEindstation = stations.index(eindstation) + 1
    verschilStations = rangnummerEindstation - rangnummerBeginstation
    prijs = verschilStations * 5
    print("Het beginstation ", beginstation, " is het ", rangnummerBeginstation, "e in het traject.", sep="")
    print("Het eindstation ", eindstation, " is het ", rangnummerEindstation, "e in het traject.", sep="")
    print("De afstand van het traject is", verschilStations, "station(s).")
    print("De ritprijs is", prijs, "euro\n")
    print("Je stapt in de trein in:", beginstation)
    for station in stations:
        if stations.index(station) > stations.index(beginstation) and stations.index(station) < stations.index(eindstation):
            print("\t-", station)
    print("Je stapt uit in:", eindstation)
    return

stations = ["schagen", "heerhugowaard", "alkmaar", "castricum", "zaandam", "amsterdam", "sloterdijk", "amsterdam centraal", "amsterdam amstel", "utrecht centraal", "’s-hertogenbosch", "eindhoven", "weert", "roermond", "sittard", "maastricht"]
print(stations)
beginstation = inlezen_beginstations(stations)
eindstation = inlezen_eindstations(stations, beginstation)
omroepen_reis(stations, beginstation, eindstation)