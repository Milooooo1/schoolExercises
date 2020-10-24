from tkinter import *
from locker import *
from IOHandling import *
import hardware_PC as hardw
import threading

global inputData
global hardThread
hardThread = threading.Thread() # placeholder


root = Tk()
def spawn_root():
    root.title("NS-Automaat")
    root.configure(background = "#FCC917")
    root.geometry("+300+200")
    root.resizable(False, False)
    root.minsize(960, 440)
    root.maxsize(960, 440)

def spawn_main_menu_grid():
    clear()
    label_1 = Label(root, text="Welkom bij NS")
    label_1.grid(columnspan=2, padx=360, pady=(100, 40))
    entry_1 = Entry(root)
    entry_1.thread = start_thread

    entry_1.grid(row=1, column=1, sticky=W)
    label_2 = Label(root, text="Voer uw OV kaart nummer in:")
    label_2.grid(row=1, column=0, sticky=E)
    button_1 = Button(root, text="Okay", command=lambda: double_button(entry_1))
    button_1.grid(row=2, columnspan=2, pady=(20, 50))
    configure_label(button_1, 12)
    configure_label(label_2, 12)
    configure_label(label_1, 24)
    root.bind("<Return>", func=lambda x: double_button(entry_1))
    local = threading.local()
    entry_1.after(500, entry_1.thread(entry_1))

def scannerThread(self):
    res = hardw.scan_ov()
    global inputData

    if(res != 0 ):
        inputData = res
        spawn_get_info_screen()

def start_thread(self):
    global hardThread

    if (hardThread.isAlive != True):
        hardThread = threading.Thread(target=scannerThread, args=(self,))
        hardThread.start()

def double_button(entry_1):
    '''Gives the ability to give two different functions with 1 button click'''
    try:
        get_entry_data(entry_1)
        spawn_get_info_screen()
        
    except:
        spawn_main_menu_grid()

def get_entry_data(entry_1):
    ''' Get the data inputted in "entry_1" '''
    global inputData
    inputData = int(entry_1.get())

def configure_label(labelName, textSize):
    '''Automatically configure labels with the NS style'''
    labelName.configure(background="#FCC917", )
    labelName.configure(font=("Frutiger", textSize, "bold"))
    labelName.configure(fg="#003082")

def clear():
    '''Clear grid of existing GUI'''
    list = root.grid_slaves()
    for l in list:
        l.destroy()

intervals = (
    ('weken', 604800),   # 60 * 60 * 24 * 7
    ('dagen', 86400),    # 60 * 60 * 24
    ('uren', 3600),      # 60 * 60
    ('minuten', 60),
    ('seconden', 1),
    )

def display_time(seconds, granularity=2):
    result = []

    for name, count in intervals:
        value = seconds // count
        if value:
            seconds -= value * count
            if value == 1:
                name = name.rstrip('s')
            result.append("{} {}".format(value, name))
    return ', '.join(result[:granularity])

def spawn_get_info_screen():
    '''
    Dialog showing the information found with the entry data if there was no data found it displays the option of hiring a locker of quitting 
    '''
    clear()
    if check_num_in_dict() == True:                                                              #Wel een kluis
        label_1 = Label(root, text="U heeft al een kluis gehuurd wat wilt u doen?")
        label_1.grid(row=0, columnspan=2, padx=180, pady=100)
        button_show_info = Button(root, text="Informatie opvragen", command=spawn_info_screen)
        button_return_locker = Button(root, text="Kluis inleveren", command=locker_returned)
        button_show_info.grid(row=1, column=1, pady=(80, 50), padx=(150, 0), sticky=W)
        button_return_locker.grid(row=1, column=0, pady=(80, 50), padx=(10,0), sticky=E)
        configure_label(button_return_locker, 16)
        configure_label(button_show_info, 16)
        configure_label(label_1, 20)

    else:                                                                                        #Geen kluis
        label_1 = Label(root, text="U heeft nog geen kluis, wilt u een kluis huren?")
        label_1.grid(row=0, columnspan=2, padx=180, pady=100)
        button_ja = Button(root, text="Ja", command=spawn_get_new_locker)
        button_nee = Button(root, text="Nee", command=spawn_main_menu_grid)
        button_ja.grid(row=1, column=1, pady=50, padx=20, sticky=W)
        button_nee.grid(row=1, column=0, pady=50, padx=20, sticky=E)
        configure_label(button_ja, 16)
        configure_label(button_nee, 16)
        configure_label(label_1, 20)
    # button_2 = Button(root, text="Go back", command=spawn_main_menu_grid)
    # button_2.grid(row=1, columnspan=2)
    # configure_label(button_2, 12)

def spawn_info_screen():
    clear()
    io.sync_data()
    lockerData = get_locker_info(int(inputData))
    hiredTime = display_time(lockerData.__deltaTime__.seconds)
    hiredTimeString = "U heeft de kluis al " + str(hiredTime) + " gehuurd."
    price = lockerData.moneyOwed
    priceSring = "Het te betalen bedrag is: €" + str(price)
    number = lockerData.lockerNum
    numberString ="U heeft kluis nummer: " + str(number)
    timesRequested = lockerData.timesRequested
    requestedString = "U heeft deze informatie al " + str(timesRequested) + " keer opgevraagd."
    header_label = Label(root, text="De informatie bij uw kluis:")
    header_label.grid(row=0, column=0, pady=(60, 20), padx=(280))
    hiredTimeLabel = Label(root, text=hiredTimeString)
    hiredTimeLabel.grid(row=1, column=0, pady=(0,10))
    priceLabel = Label(root, text=priceSring)
    priceLabel.grid(row=2, column=0, pady=(0,10))
    requestLabel = Label(root, text=requestedString)
    requestLabel.grid(row=3, column=0, pady=(0,10))
    numberLabel = Label(root, text=numberString)
    numberLabel.grid(row=4, column=0, pady=(0,50))
    button_back = Button(root, text="Ga terug", command=spawn_main_menu_grid)
    button_back.grid(row=5, column=0, sticky=N, pady=(0,50))

    configure_label(button_back, 16)
    configure_label(numberLabel, 10)
    configure_label(requestLabel, 10)
    configure_label(priceLabel, 10)
    configure_label(hiredTimeLabel, 10)
    configure_label(header_label, 24)
    root.bind("<Return>", func=lambda x:spawn_main_menu_grid)

def spawn_get_new_locker():
    '''
    Dialog showing that you hired a locker and adding it to the dictionary and syncing it.
    '''
    clear()
    label_1 = Label(root, text="U heeft een kluis gehuurd.")
    label_1.grid(row=0, column=0, pady=(150,50), padx=320)
    button_back = Button(root, text="Okay", command=spawn_main_menu_grid)
    button_back.grid(row=1, column=0, pady=(0, 50))
    configure_label(button_back, 16)
    configure_label(label_1, 20)
    add_locker(int(inputData))
    io.sync_data()
    root.bind("<Return>", func=lambda x:spawn_main_menu_grid)

def check_num_in_dict():
    '''
    Checks if the card number that has been inputted already has a registered locker. 
    Return value True = Does have a registered locker. False = Does not have a registered locker.
    '''
    numList = []
    for locker in io.internalDataBuffer:
        try:
            numList.append(io.internalDataBuffer[locker]["cardNum"])
        except:
            break
    if int(inputData) in numList:
        return True
    else:
        return False

def locker_returned():
    '''
    Deletes locker from json file and shows the price you owe.
    '''
    price = float(get_locker_info(int(inputData)).moneyOwed)
    labelText = "Het te betalen bedrag is: €" + str(price)
    return_locker(int(inputData))
    clear()
    io.sync_data()
    label_1 = Label(root, text="Bedankt voor het gebruiken van de NS kluisverhuur.")
    label_1.grid(row=0, columnspan=2, pady=(100), padx=(130))
    label_2 = Label(root, text=labelText)
    label_2 .grid(row=1, columnspan=2, pady=(10,20))
    button_back = Button(root, text="Ga terug", command=spawn_main_menu_grid)
    button_back.grid(row=2, columnspan=2, pady=(0,50))
    configure_label(button_back, 16)
    configure_label(label_2, 12)
    configure_label(label_1, 20)
    root.bind("<Return>", func=lambda x:spawn_main_menu_grid)

