#opdracht 8_1 While-Loop & Numbers
som = []
while(1):
    getal = int(input("Geef een getal: "))
    if getal == 0:
        print("u heeft", str(len(som)), "ingevoerd, de som is:", str(sum(som)))
        break
    else:
        som.append(getal)