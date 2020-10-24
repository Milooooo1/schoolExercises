#Opdracht 6_4 Files schrijven
import datetime
registratie = open("hardlopers.txt", "w")
vandaag = datetime.datetime.today()
s = vandaag.strftime("%a %d %b %Y")
currentDT = datetime.datetime.now()
running = True
while running:
    register = input("Wilt u een hardloper regristreren? Antwoord met Y of N:")
    if register.lower() == "y":
        naam = input("Geef de hardlopers naam op:")
        registratie.write(str(s) +  " " +   str(currentDT.hour) + ":"+ str(currentDT.minute)+  ":"+ str(currentDT.second)+ ", "+ naam + "\n" )
    elif register.lower() == "n":
        running = False
    else:
        print("U heeft een typfout gemaakt probeer het opnieuw")
registratie.close()