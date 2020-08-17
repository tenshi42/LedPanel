import time

import signal

from PanelWriter import PanelWriter

text = "TEST"

pan = None


def sigint_handler(signum, frame):
    pan.isRunning = False

signal.signal(signal.SIGINT, sigint_handler)

def main():
    global text
    global pan

    pan = PanelWriter(800, 4)
    pan.Write(text)
    pan.start()

    while pan.isRunning:
        text = "TEST"
        pan.Write(text)
        time.sleep(0.5)

main()

