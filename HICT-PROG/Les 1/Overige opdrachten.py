import math
#Les 3
c = math.sqrt(((3**2) * (4**2)))
print(c)
print(c == 5)
a = math.pi * (10**2)
print(a)
print(5 < 7 and 5 > -7)
naam = input("Schrijf hier je naam: ")
leeftijd = int(input("Schrijf hier je leeftijd: "))
print(naam, "je bent volgend jaar dus", leeftijd + 1)
if leeftijd >= 18:
    print(naam, "je mag al stemmen!")
else:
    print(naam, "je mag helaas nog niet stemmen.")