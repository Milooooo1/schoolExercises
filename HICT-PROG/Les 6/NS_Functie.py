#Opdracht NS_Functie
def standaardrit(afstandKM):
    standaardprijs = 0
    if (afstandKM < 0):
        afstandKM = 0
    if (afstandKM < 50):
        standaardprijs = afstandKM * 0.80
    elif(afstandKM >= 50):
        standaardprijs = (afstandKM - 50) * 0.60 + 15
    else:
        print("Invalid value")
    return standaardprijs

def ritprijs(leeftijd, weekendrit, afstandKM):
    prijs = standaardrit(afstandKM)
    if (leeftijd < 12 or leeftijd >= 65):
        if(weekendrit == True):
            prijs = prijs - (prijs * 0.35)
        elif(weekendrit == False):
            prijs = prijs - (prijs * 0.30)
    else:
        if(weekendrit == True):
            prijs = prijs - (prijs * 0.40)
    return prijs

print(ritprijs(8, True, 49))
print(ritprijs(8, False, 49))
print(ritprijs(8, True, 50))
print(ritprijs(8, False, 50))
print(ritprijs(12, True, -10))
print(ritprijs(12, False, 28))
print(ritprijs(65, True, 50))
print(ritprijs(64, True, 49))
print(ritprijs(64, False, 49))
print(ritprijs(64, False, 50))
print(ritprijs(64, True, 50))

