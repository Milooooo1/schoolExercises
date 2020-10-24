#Opdracht 9_1 Sets
groen = {"Boxtel", "Best", "Beukenlaan", "Eindhoven", "Geldrop", "Heeze", "Weert"}
bruin = {"Boxtel", "Best", "Beukenlaan", "Eindhoven", "Helmond 't Hout", "Helmond", "Helmond Brouwhuis", "Deurne"}
overeenkomst = groen.intersection(bruin)
print(overeenkomst)
verschil = bruin.difference(groen)
print(verschil)
totaal = groen.union(bruin)
print(totaal)