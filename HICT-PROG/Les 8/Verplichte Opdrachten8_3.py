#Opdracht 8_3 Dict
cursusCijfers = {
    "Milo": 8,
    "Jasper": 5,
    "Lucas": 7,
    "Jan": 9,
    "Hans": 4,
    "Pieter": 9,
    "Thomas": 6,
    "Edwin": 9
}
for(key, value) in cursusCijfers.items():
    if value >= 9:
        print(key, str(value))
