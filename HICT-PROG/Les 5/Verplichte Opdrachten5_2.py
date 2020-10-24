#Opdracht 5_2 Functie met list-Parameter
def som(getallenLijst):
    optelling = 0
    for cijfer in getallenLijst:
        optelling = optelling + cijfer
        print(optelling)
    return optelling

getallenLijst = [1, 6, 2, 6, 8, 9, 2, 3, 4, 2]
som(getallenLijst)