#Opdracht8_5
def namen():
    namen = {}
    namenLijst = []
    running = True
    while running:
        naam = input("Voer een naam in: ")
        if naam != " ":
            if naam != namenLijst:
                namenLijst.append(naam)
        else:
            running = False

    for naam in namenLijst:
        aantal = namenLijst.count(naam)
        namen.update({naam: aantal})

    return(namen)

print(namen())