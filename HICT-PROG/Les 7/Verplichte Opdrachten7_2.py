#Opdracht 7_2 List & Numbers
invoer = "5-9-7-1-7-8-3-2-4-8-7-9"
getallen = invoer.split("-")
getallen.sort()
for i in range(len(getallen)):
    getallen[i] = int(getallen[i])
print(getallen)
print("Het kleinste getal is: " + str(getallen[0]))
print("Het grootste getal is: " + str(getallen[-1]))
print("Het aantal getallen is: " + str(len(getallen)) + " En de som van de getallen is: " + str(sum(getallen)))
print("Het gemiddelde van de lijst is: " + str((sum(getallen)/len(getallen))))
