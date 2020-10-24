import json
with open(r"C:\Users\Milo\OneDrive - Stichting Hogeschool Utrecht\Cursus Programmeren\Les 11\stationslijst.json", "r") as jsonFile:
    data = json.load(jsonFile)
    print("Dit zijn de namen, codes en types van elk station:")
    n = 0
    for station in data["payload"]:
        print("{:25s}{:4s}{:7s}{:4s}{}".format(
            data["payload"][n]["namen"]["lang"], "-", data["payload"][n]["code"], ":", data["payload"][n]["stationType"]))
        n += 1
    longitudeLijst = []
    n2 = 0
    for station in data["payload"]:
        longitudeLijst.append(data["payload"][n2]["lng"])
        n2 += 1
    positie = longitudeLijst.index(max(longitudeLijst))
    print("Het meest oostelijke station is:",
          data["payload"][positie]["namen"]["lang"])
