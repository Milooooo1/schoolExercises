import json
with open(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 11\loginLogs.json", "w") as jsonFile:
    output = []
    running = True
    while running:
        achternaam = str(input("Wat is je achternaam: "))
        if achternaam == "einde":
            running = False
        else:
            persoonsGegevens = {
            "achternaam": achternaam,
            "voorletters": str(input("Wat zijn je voorletters: ")),
            "gebDatum": str(input("Wat is je geboortedatum: ")),
            "e-mail": str(input("Wat is je e-mail adres: "))
            }
            output.append(persoonsGegevens)

    jsonFile = json.dump(output, jsonFile, indent=4)