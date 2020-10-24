#3.3 Input/Output
running = True
while running:
    uurloon = input("Wat verdien je per uur: ")
    aantalUur = input("Hoeveel uur heb je gewerkt deze week: ")
    try:
        salaris = float(uurloon) * float(aantalUur)
        print("Je salaris na", aantalUur, "uur werken levert", salaris, "euro op")
        running = False
    except ValueError:
        print("U mag alleen getallen invoeren.")
    except:
        print("Oeps, er is iets onverwachts gebeurd probeer het opnieuw.")