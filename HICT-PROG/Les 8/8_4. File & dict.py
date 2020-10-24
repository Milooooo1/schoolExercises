def ticker(filename):
    exDict = {}
    file = open(filename)
    for i in file.readlines():
        fullLine = i.split(':')
        exDict[fullLine[0]] = fullLine[1].rstrip('\n')
        print(exDict)
    return exDict

def bedrijfTick(input):
    exDict = ticker(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 8\bedrijven.txt")
    return print('Ticker symbol: '+ exDict[input])

def tickBedrijf(input):
    exDict = ticker(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 8\bedrijven.txt")
    for bedrijf,tick in exDict.items():
        if tick == input:
            return print('Company name: '+ bedrijf)


ticker(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 8\bedrijven.txt")
bedrijfTick(input('Enter company name: '))
tickBedrijf(input('Enter ticker symbol: '))
