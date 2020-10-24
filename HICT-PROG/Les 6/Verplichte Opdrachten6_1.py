#Opdracht 6_1 Formatting
def convert(tempC):
    tempF = (tempC * 1.8) + 32
    return tempF

def table(tempC):
    print("{:>6} {:>9}".format("F", "C"))
    for tempC in range(-30, 41, 10):
        tempF = convert(tempC)
        print("{:>8.1f} {:>8.1f}".format(tempF, float(tempC)))

print(table(0))