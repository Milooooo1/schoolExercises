#Opdracht 5_6 Functie met (im)mutable parameter
def wijzig(letterlijst):
    letterlijst.clear()
    letterlijst.extend(['d', 'e', 'f'])

letterlijst = ['a', 'b', 'c']
print(letterlijst)
wijzig(letterlijst)
print(letterlijst)
