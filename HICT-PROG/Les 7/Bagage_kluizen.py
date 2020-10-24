#Opdracht Bagage kluizen
def freeLockers():                                                                                              #Werkt
    aantalLockersInGebruik = kluizen.readlines()
    aantalVrijeLockers = 12 - len(aantalLockersInGebruik)
    print(aantalVrijeLockers)

def nieuweKluis():                                                                                              #Werkt
    vrijeLockers = [1,2,3,4,5,6,7,8,9,10,11,12]
    gebruikteLockers = kluizen.readlines()
    for item in gebruikteLockers:
        subitem = item.split(";")
        item = subitem[0]
        vrijeLockers.remove(int(item))
    if len(vrijeLockers) == 0:
        return "Sorry er zijn geen kluizen beschikbaar."
    else:
        print("Er is een kluis gevonden, u heeft kluisnummer:", str(vrijeLockers[0]))
        kluiscode = input(print("Voer nu uw code in: "))
        if len(kluiscode) < 4:
            print("Uw kluiscode moet langer zijn dan 4 karakters. Probeer het opnieuw.")
            kluiscode = input(print("Voer nu uw code in: "))
        kluizen.write("\n"+str(vrijeLockers[0])+";"+kluiscode)
        return "Uw kluis is vergrendeld."

def kluisOpenen():                                                                                              #Werkt
    kluisNummer = int(input("Wat is uw kluisnummer?"))
    kluisCode = input("Wat is uw kluiscode?")
    invoer = (str(kluisNummer)+ ";"+ str(kluisCode)+"\n")
    gebruikteLockers = kluizen.readlines()
    for kluis in gebruikteLockers:
        if kluis == invoer:
            print("Uw kluis is geopend")
            return
    print("Er is geen kluis gevonden met de ingevulde gegevens.")

def kluisTeruggeven():                                                                                          #Werkt
    kluisNummer = int(input("Wat is uw kluisnummer?"))
    kluisCode = input("Wat is uw kluiscode?")
    invoer = (str(kluisNummer)+ ";"+ str(kluisCode)+"\n")
    gebruikteLockers = kluizen.readlines()
    for kluis in gebruikteLockers:
        if kluis == invoer:
            gebruikteLockers.remove(kluis)
            print("Uw kluis is ingeleverd, bedankt voor het gebruiken.")
            print(gebruikteLockers)
            with open("kluizen.txt", "w") as f:
                for kluis in gebruikteLockers:
                    f.write(kluis)
            return
    print("Er is geen kluis gevonden met deze gegevens.")

running = True
while running == True:
    kluizen = open("kluizen.txt", "r+")
    print("1: Ik wil weten hoeveel kluizen nog vrij zijn\n", "2: Ik wil een nieuwe kluis\n", "3: Ik wil even iets uit mijn kluis halen\n", "4: Ik geef mijn kluis terug\n", "5: Ik ben klaar", sep="")
    actieNummer = int(input("Wat wilt u doen? Voer het nummer van de actie in:"))
    if actieNummer == 1:
        freeLockers()
        kluizen.close()
    elif actieNummer == 2:
        nieuweKluis()
        kluizen.close()
    elif actieNummer == 3:
        kluisOpenen()
        kluizen.close()
    elif actieNummer == 4:
        kluisTeruggeven()
        kluizen.close()
    elif actieNummer ==5:
        running = False
        kluizen.close()
    else:
        print("U heeft een verkeerd nummer ingevuld.")