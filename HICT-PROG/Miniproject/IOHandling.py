import json


def dict_init(num):
    "This function initializes the programs buffer, which i"
    global internalDataBuffer

    try:
        f = open("data.json", "r")
        internalDataBuffer = json.load(f)
        f.close()

    except IOError:
        f = open("data.json", "w")
        internalDataBuffer = {}

        for i in range(1, num+1):
            internalDataBuffer.update( { i : {
        "cardNum" : 0,
        "vacant" : True,
        "time" : "NULL",
        "numDataRequested" : 0
        } } ) 

        json.dump(internalDataBuffer, f, indent=4)         # dump empty dict in file
        f.close()

    return


def sync_data():
    
    with open("data.json", "w") as f:
        json.dump(internalDataBuffer, f, indent=4)

