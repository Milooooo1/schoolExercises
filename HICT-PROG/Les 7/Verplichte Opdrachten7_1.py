#Opdracht 7_1 Decision Control
def seizoen(maand):
    if (maand >= 3 and maand <= 5):
        return "lente"
    elif (maand >= 6 and maand <=8):
        return "zomer"
    elif (maand >=9 and maand <=11 ):
        return "herfst"
    elif (maand == 12 or maand == 1 or maand ==2):
        return "winter"
    else:
        return "invalid value"

print(seizoen(1))
