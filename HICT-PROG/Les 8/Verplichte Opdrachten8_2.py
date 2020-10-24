#opdracht 8_2 While-loop & strings
while(1):
    invoer = str(input("Geef een string van 4 letters: "))
    if len(invoer) == 4:
        print("Invoer van correcte string:", invoer, "is geslaagd.")
        break
    else:
        print(invoer, "heeft", str(len(invoer)), "letters")