bedrag = 4356
aantalMensen = input("Hoeveel mensen gaan er mee? ")
try:
    if int(aantalMensen) < 0:
        raise AssertionError
    print(bedrag / int(aantalMensen))
except ZeroDivisionError:
    print("Delen door nul kan niet!")
except AssertionError:
    print("Negatieve getallen zijn niet toegestaan!")
except ValueError:
    print("Gebruik cijfers voor het invoeren van het getal!")
except:
    print("Onjuiste invoer")