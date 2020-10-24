
#Opdrachten 1.2 Strings
print(len("Supercalifragilisticexpialidocious"))

print("ice" in "Supercalifragilisticexpialidocious")

print(len("Supercalifragilisticexpialidocious") > len("Honorificabilitudinitatibus")) 

listOfStrings = ["Berlioz", "Borodin", "Brian", "Bartok", "Bellini", "Buxtehude", "Bernstein"]

print(listOfStrings)

listOfStrings.sort()

print(listOfStrings[0])
print(listOfStrings[-1])

#Opdrachten 1.3 Statements
a = 6
b = 7
c = ((a + b)/ 2)
print(c)

voornaam = "Milo"
achternaam = 'Beliën'
tussenvoegsel = "nvt"
mijnNaam = voornaam + " " + achternaam
print(mijnNaam)

#Opdrachten 1.4 Expressions
print(75 > a and 75 < b)
print(len(mijnNaam) == len(voornaam + achternaam))
print(len(mijnNaam) > (5 * len(tussenvoegsel)))
print(tussenvoegsel in mijnNaam)

