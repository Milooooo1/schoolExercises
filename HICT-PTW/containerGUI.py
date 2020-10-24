from tkinter import *
from container import *


def refresh():
    checkDepth()

    try:
        with open("DataBase.json", "r") as f:
            loadedData = json.load(f)
    except IOError:
        print("The file DataBase.json has not been found!")

    locationLabel['text'] = "{}".format(loadedData[containerID]["location"])
    percentageLabel['text'] = "Filled percentage: {}%".format(loadedData[containerID]["filled percentage"])

    imagePriority = globals()["imagePriority" + str(loadedData[containerID]["priority level"])]
    containerLabel.configure(image=imagePriority)


root = Tk()
root.attributes('-fullscreen', True)

screenWidth = root.winfo_screenwidth()
screenHeight = root.winfo_screenheight()

imageLogo = PhotoImage(file=r"Images/HULogo.png")
imageRefresh = PhotoImage(file=r"Images/RefreshKnop.png")
imagePriority0 = PhotoImage(file=r"Images/PrullenbakPrio0.png")
imagePriority1 = PhotoImage(file=r"Images/PrullenbakPrio1.png")
imagePriority2 = PhotoImage(file=r"Images/PrullenbakPrio2.png")
imagePriority3 = PhotoImage(file=r"Images/PrullenbakPrio3.png")
imageExit = PhotoImage(file=r"Images/ExitButton.png")

infoFrame = Frame(root, width=screenWidth * 0.8, height=screenHeight * 0.2, background="white")
infoFrame.grid(row=0, column=0)

containerFrame = Frame(root, width=screenWidth * 0.8, height=screenHeight * 0.6, background="white")
containerFrame.grid(row=1, column=0)

refreshFrame = Frame(root, width=screenWidth * 0.8, height=screenHeight * 0.2, background="white")
refreshFrame.grid(row=2, column=0)

logoFrame = Frame(root, width=screenWidth * 0.2, height=screenHeight, background="white")
logoFrame.grid(row=0, column=1, rowspan=3)

checkDepth()

try:
    with open("DataBase.json", "r") as f:
        readData = json.load(f)
except IOError:
    print("The file DataBase.json has not been found!")

locationLabel = Label(master=infoFrame, text="{}".format(readData[containerID]["location"]), font=("Century Gothic", 32),
                      bg="white", fg="blue")
locationLabel.place(relx=0.6, rely=0.3, anchor=CENTER)

percentageLabel = Label(master=infoFrame, text="Filled percentage: {}%".format(readData[containerID]["filled percentage"]),
                        font=("Century Gothic", 32), bg="white", fg="red")
percentageLabel.place(relx=0.6, rely=0.7, anchor=CENTER)

imagePriority = globals()["imagePriority" + str(readData[containerID]["priority level"])]

containerLabel = Label(master=containerFrame, image=imagePriority, bg="white")
containerLabel.place(relx=0.6, rely=0.5, anchor=CENTER)

priorityLabel = Label(master=containerFrame, text="Priority", font=("Century Gothic", 26), bg="white", fg="red")
priorityLabel.place(relx=0.6, rely=0.9, anchor=CENTER)

refreshButton = Button(master=refreshFrame, image=imageRefresh, bg="white", command=refresh)
refreshButton.place(relx=0.6, rely=0.5, anchor=CENTER)

exitButton = Button(master=logoFrame, image=imageExit, bg="white", bd=0, command=exit)
exitButton.place(relx=0.75, rely=0.06, anchor=CENTER)

logoLabel = Label(master=logoFrame, image=imageLogo, bg="white")
logoLabel.place(relx=0.5, rely=0.85, anchor=CENTER)

root.mainloop()
