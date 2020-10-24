#Opdracht 5_3 Functie met if
def lang_genoeg(lengte):
    if lengte >= 120:
        print("Je bent lang genog voor deze attractie!")
    else:
        print("Sorry, je bent niet lang genoeg.")

lengte = int(input("Voer hier uw lengte in centimeters in: "))
lang_genoeg(lengte)