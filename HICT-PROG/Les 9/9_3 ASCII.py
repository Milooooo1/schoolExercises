#Opdracht 9_3
def code(inputString):
    charList =[]
    letterList =[]
    for char in inputString:
        charList.append(ord(char)+3)
    #print(charList)
    for letter in charList:
        letterList.append(chr(letter))
    #print(letterList)
    outputString = "".join(letterList)
    return outputString

print(code("MiloCulemborgUtrecht Centraal"))