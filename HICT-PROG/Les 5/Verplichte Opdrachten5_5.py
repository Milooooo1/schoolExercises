#Opdracht 5_5 Functie met list paramter en for-loop
def kwadraten_som(grondgetallen):
    tempList=[]
    for cijfer in grondgetallen:
        if (cijfer > 0):
            tempList.append(cijfer * cijfer)
    print(sum(tempList))

kwadraten_som([4, 5, 3, -81])