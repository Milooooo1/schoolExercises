import IOHandling as io
import GUI
import bot

import threading

def start_bot_thread():
    updater = bot.Updater(token="953767096:AAH535LMdx7fsYSJ5SWxtR1QvXCFlKKYK2k", use_context=True)
    dispatcher = bot.construct_dispatcher(updater)
    updater.start_polling()
    return

def start_gui_thread():
    inputData = int()
    GUI.spawn_root()
    GUI.spawn_main_menu_grid()
    GUI.mainloop()
    return

io.dict_init(100)

#Create a separate thread for the bot
botThread = threading.Thread(target=start_bot_thread)
botThread.start()

start_gui_thread() #tkinter must be on the main thread

botThread.join()


