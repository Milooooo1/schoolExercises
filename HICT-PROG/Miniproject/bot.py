from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram.ext import messagehandler
from telegram.ext import filters
from telegram import replykeyboardmarkup, replymarkup, keyboardbutton
import locker

#   This dict is used to bind a chat to a cardNumber
cardNums = {}

#   This is the keyboard used by the bot
botMarkup = replykeyboardmarkup.ReplyKeyboardMarkup ( [
    
        [
        keyboardbutton.KeyboardButton("Hoe lang staat mijn fiest al in de stalling?"),
        keyboardbutton.KeyboardButton("Hoe veel kost mij dat?")
        ],

        [
        keyboardbutton.KeyboardButton("Welk kluisnummer had ik ook al weer?"),
        keyboardbutton.KeyboardButton("Ik wil alles weten")
        ]
]
)

#   The four functions below return the appropriate data from a __Locker class,
#   the functions are used to obfuscate the class because these are not part of the course.
def get_time(locker):
    return str(round(locker.__deltaTime__.seconds/3600)) + " uur"


def get_money_owed(locker):
    return (str(locker.moneyOwed) + " EUR")


def get_num(locker):
    return str("Het nummer van uw kluis is " + locker.lockerNum)


def get_all(locker):
    time, owed, num = locker.__deltaTime__, locker.moneyOwed, locker.lockerNum
   
    return str("De fiets staat al " + str(round(time.seconds/3600)) + " uur in de locker, \n\
Om hem terug te krijgen zal u " + str(owed) + " Euro moeten betalen,\n\
Hij is te vinden in locker " + str(1)) 
     
#   Bind text to a function
functions = {
    "Hoe lang staat mijn fiest al in de stalling?" : get_time,
    "Hoe veel kost mij dat?" : get_money_owed,
    "Welk kluisnummer had ik ook al weer?" : get_num,
    "Ik wil alles weten": get_all
}

def __start(update, context):
    "This function is used by the bot to handle the /start command."

    tmpId = update.effective_chat.id
    context.bot.send_message(chat_id=tmpId, text="Wat is je kaartnummer?")
    
    try:
        cardNums[tmpId] = 0
    
    except:
        cardNums.update({ tmpId : 0 })

def __text_handler(update, context):
    "This function is used by the bot to handle text (keyboard buttons)."

    if (cardNums[update.effective_chat.id] == 0):

        try:
            cardNums[update.effective_chat.id] = int(update.effective_message.text)
            context.bot.send_message(chat_id=update.effective_chat.id, text="OK", reply_markup=botMarkup)

        except:
            context.bot.send_message(chat_id=update.effective_chat.id, text="Heel grappig, dat is niet eens een nummer.")

    else:

        try:
            cardNum = cardNums[update.effective_chat.id]
            Locker = locker.get_locker_info(cardNum)

            if(Locker.timesRequested >= 7):
                message = "Joh, je hebt dit nou al " + str(Locker.timesRequested) + " keer opgevraagt, misschien is het een idee om de fiets op te halen?"
                context.bot.send_message(chat_id=update.effective_chat.id, text=message)

            elif(Locker.timesRequested >= 5):
                message = "Bot zij is hard werken, je hebt al " + str(Locker.timesRequested) + " keer informatie over je locker opgevraagt."
                context.bot.send_message(chat_id=update.effective_chat.id, text=message)

            retMessage = functions[update.effective_message.text](Locker)
            context.bot.send_message(chat_id=update.effective_chat.id, text=retMessage)

        except:
            context.bot.send_message(chat_id=update.effective_chat.id, text="Er is ergens iets niet goed gegaan, is dit een bestaande kluis?")


def construct_dispatcher(updater):
    "This function adds the handlers to the Updater(bot) object."

    dispatcher = updater.dispatcher

    dispatcher.add_handler(CommandHandler('start', __start))
    dispatcher.add_handler(messagehandler.MessageHandler(filters.Filters.text, __text_handler))

    return dispatcher
