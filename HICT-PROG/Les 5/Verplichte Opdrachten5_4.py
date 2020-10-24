#Opdracht 5_4 Functie met if
def new_password(oldPassword, newPassword):
    if newPassword != oldPassword and len(newPassword) >= 6 and any(char.isdigit() for char in newPassword):
        return("True")
    else:
        return("False")

print(new_password("qwerty", "qwertyuiop1"))