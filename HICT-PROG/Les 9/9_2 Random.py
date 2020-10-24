#Opdracht 9_2 Random
import random
def monopolyworp():
    running = True
    dubbelCount = 0
    gevangenis = False
    while running:
        dobbelsteen1 = random.randrange(1,7)
        dobbelsteen2 = random.randrange(1,7)
        if dobbelsteen1 == dobbelsteen2:
            running = True
            dubbelCount += 1
            print("U mag nog een keer gooien")
        else:
            running = False
        if dubbelCount == 3:
            gevangenis = True
        if gevangenis == True:
            print(dobbelsteen1, "+", dobbelsteen2, "=", "(direct naar de gevangenis)")
        else:
            print(dobbelsteen1, "+", dobbelsteen2, "=", dobbelsteen1 + dobbelsteen2)
    return dobbelsteen1, dobbelsteen2

monopolyworp()
