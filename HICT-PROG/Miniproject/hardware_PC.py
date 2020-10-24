import socket

def scan_ov():
    # maakt verbinding met de python code op de Pi
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        s.connect(("192.168.42.1", 1234))
    except:
        return 0   # Function is sheduled by Tk-inter, it would not be smart to implement recursion.

    msg = s.recv(1024)
    s.close()

    # maakt van de gekregen data een nummer
    OV_kaartnummer = ""
    msg_list = msg.decode("utf-8").split(", ")
    msg_list[0] = msg_list[0][1:]
    msg_list[-1] = msg_list[-1][:-1]

    for item in msg_list:
        OV_kaartnummer = OV_kaartnummer + item

    return OV_kaartnummer

# scan_ov()