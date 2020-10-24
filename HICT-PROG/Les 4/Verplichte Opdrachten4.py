#Opdracht 4_3 if with 2 boolean operators
leeftijd = int(input("Geef uw leeftijd:"))
paspoort = input("Geef aan met 'ja' of 'nee' of u een Nederlands paspoort bezit:")
if leeftijd >= 18 and "ja" in paspoort:
    print("Gefeliciteerd u mag stemmen!")
else:
    print("Helaas, u mag niet stemmen. Als u denkt dat dit niet klopt kan het zijn dat u een typfout heeft gemaakt probeer het dan opnieuw.")

#Opdracht 4_4 For, If & Strings
weekDagen = ['Maandag', 'Dinsdag', 'Woensdag', 'Donderdag', 'Vrijdag', 'Zaterdag', 'Zondag']
for x in weekDagen:
    print(x[0:2])

#Opdracht 4_5 For, If & Numbers
for i in range(20):
    if i % 2 == 0:
        print(i)

#Opdracht 4_6 For, If & Vowels
s = "Guido van Rossum heeft programmeertaal Python bedacht."
klinkers = ['a', 'e', 'o', 'u', 'i']
for char in s:
    if char in klinkers:
        print(char)