from pirc522 import RFID
import socket
import time

rdr = RFID()

# socket stuk 1
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('0.0.0.0', 1234))
s.listen(5)

try:
    while True:
        rdr.wait_for_tag()
        (error, tag_type) = rdr.request()

        if not error:
            print("Tag detected")
            (error, uid) = rdr.anticoll()

            if not error:
                print("UID: " + str(uid)) # Select Tag is required before Auth

                if not rdr.select_tag(uid): # Auth for block 10 (block 2 of sector 2) using default shipping key A

                    if not rdr.card_auth(rdr.auth_a, 10, [0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF], uid):
                        # This will print something like (False, [0, 0, 0, 0, 0, 0, 0, 0, 0$
                        print("Reading block 10: " + str(rdr.read(10)))

                        # Always stop crypto1 when done working
                        rdr.stop_crypto()

                # socket stuk 2

                while True:
                    clientsocket, address = s.accept()
                    print(f"Connection from {address} has been established!")
                    # temp_code = input("voer test nummer in: ")
                    clientsocket.send(bytes(str(uid), "utf-8"))
                    break
                time.sleep(5)

except:
    print('exception')
finally: # Calls GPIO cleanup
    rdr.cleanup()