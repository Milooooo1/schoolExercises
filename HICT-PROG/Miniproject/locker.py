import IOHandling as io
import datetime
import math


class __Locker:
    """A class containing all variables needed to show data to user,\n
    way easier to work with than a raw dictionary or tulple."""

    def __init__(self, cardNum):

        tmp = get_locker_from_card(cardNum)

        locker = io.internalDataBuffer[tmp]

        locker["numDataRequested"] += 1

        self.lockerNum = tmp
        self.cardNum = locker["cardNum"]
        self.timesRequested = locker["numDataRequested"]
        self.timeAcquired = locker["time"]
        self.__deltaTime__ = datetime.datetime.now() - datetime.datetime.strptime(self.timeAcquired, "%Y-%m-%d %H:%M")
        
        # Calculating the price will be done in this constructor, writing a function for it doesn't make much sense.
        self.moneyOwed = math.ceil(self.__deltaTime__.seconds/3600) * 23 # TODO: define hourly rate


def get_vacant_locker():
    "Returns the fist locker that is vacant"
   
    for locker in io.internalDataBuffer:
        if io.internalDataBuffer[locker]["vacant"] == True:
            return locker

    return 0

def get_locker_info(cardNum):
    """Returns a __Locker class, classes are not covered in the course,\n
        so this function exists to obfuscate the class."""

    return __Locker(cardNum)

def get_locker_from_card(cardNum):
    "Returns the number from the locker assigned to the Card number"

    return list(io.internalDataBuffer.keys())[list(io.internalDataBuffer[key]["cardNum"] == cardNum for key in io.internalDataBuffer).index(1)]


def locker_on_pass(cardNum):

    if (any(io.internalDataBuffer[locker]["cardNum"] == cardNum for locker in io.internalDataBuffer)):
        return True

    return False


def add_locker(cardNum):
    "Add locker to the internalDataBuffer and returns the number of the locker assigned to user"

    lockerNum = get_vacant_locker()

    io.internalDataBuffer[lockerNum] = {
        "cardNum" : cardNum,
        "vacant" : False,
        "time" : datetime.datetime.strftime(datetime.datetime.now(), "%Y-%m-%d %H:%M"),
        "numDataRequested" : 0
    } 

    return lockerNum


def return_locker(cardNum):
    "Remove locker from the internalDataBuffer"

    io.internalDataBuffer[ get_locker_from_card(cardNum) ] = {
        "cardNum" : 0,
        "vacant" : True,
        "time" : "NULL",
        "numDataRequested" : 0
    } 
    