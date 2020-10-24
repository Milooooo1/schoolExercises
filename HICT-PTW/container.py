import json
import sensor

threshold = 0.01
baseDepth = 0
normalDepth = 60
holidayDepth = 50
holiday = False
minimumDepth = holidayDepth if holiday else normalDepth
maximumDepth = 100
oldDepthPercentage = -1

location = "Heidelberglaan 15"
containerID = "0"


def getDepthPercentage():
    # Reading depth sensors and getting the first 3 variables from the other file.
    return int(mapFromTo(sensor.getData(), sensor.minCheck, sensor.maxCheck, 100, 0))


def setData(depthPercentage):
    depthPercentage = max(0, min(depthPercentage, 100))
    
    # Upload to database.
    priority = getPriority(depthPercentage)
    data = \
    {
        containerID: {
            "location": location,
            "filled percentage": depthPercentage,
            "priority level": priority
        }
    }
    writeData = {}

    with open("DataBase.json", "r") as f:
        try:
            readData = json.load(f)
            if containerID not in readData.keys():  # New container with a new id.
                writeData = {**readData, **data}
            else:  # Already existing container.
                readData[containerID] = data[containerID]
                writeData = {**readData, **data}
        except json.JSONDecodeError:  # If JSON is empty just write this container info.
            writeData = data

    with open("DataBase.json", "w") as f:
        json.dump(writeData, f, indent=4)

    f.close()


def checkDepth():
    global oldDepthPercentage
    depthPercentage = getDepthPercentage()
    if depthPercentage != oldDepthPercentage and \
    (depthPercentage > oldDepthPercentage + threshold or oldDepthPercentage + threshold > maximumDepth
     or depthPercentage < oldDepthPercentage - threshold):
        setData(depthPercentage)
    oldDepthPercentage = depthPercentage


def getPriority(depthPercentage):
    # Checks which priority level the container should be.
    priority = 0
    if holiday:
        if holidayDepth <= depthPercentage < 65:
            priority = 1
        elif 65 <= depthPercentage < 75:
            priority = 2
        elif 75 <= depthPercentage:
            priority = 3
    else:
        if normalDepth <= depthPercentage < 70:
            priority = 1
        elif 70 <= depthPercentage < 85:
            priority = 2
        elif 85 <= depthPercentage:
            priority = 3
    return priority


def mapFromTo(x, a, b, c, d):
    y = (x - a) / (b - a) * (d - c) + c
    return y

