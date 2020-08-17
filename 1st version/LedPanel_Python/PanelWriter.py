import threading
import RPi.GPIO as GPIO
from converter import *
import time


class PanelWriter(threading.Thread):
    def __init__(self, frequency, nbpanels):
        threading.Thread.__init__(self)
        self.text = ""
        self.frequency = frequency
        self.nbPanels = nbpanels
        self.isRunning = True
        self.powerPos = 0
        self.maxPowerPos = self.nbPanels * 3

        self.pinList = [2, 3, 4, 17, 27, 22, 10, 9, 11, 5, 6, 13, 19, 26]
        self.syncPin = 18
        self.resetPin = 23

        self.syncState = True
        self.syncReset = False

        GPIO.setmode(GPIO.BCM)

        self.panelData = np.ones((6*nbpanels, 7)).astype(int)
        self.initGPIO()

    def Write(self, text):
        self.text = text
        self.panelData = np.zeros((6 * self.nbPanels, 7)).astype(int)
        self.panelData += ((textToBinMatrix(self.text) + 1) % 2)[:6 * self.nbPanels]

    def SetFrequency(self, frequency):
        self.frequency = frequency

    def run(self):
        GPIO.output(self.resetPin, self.syncReset)
        self.syncState = not self.syncReset
        while self.isRunning:
            self.writeLine(list(np.concatenate((
                self.panelData[((self.powerPos+11) % self.maxPowerPos)*2],
                self.panelData[((self.powerPos+11) % self.maxPowerPos)*2+1]
            ))))
            self.powerPos += 1
            GPIO.output(self.syncPin, self.syncState)
            self.syncState = not self.syncState

            if self.powerPos % self.maxPowerPos == 0:  # Sync
                GPIO.output(self.resetPin, self.syncReset)
                self.syncState = not self.syncReset
                print("sync")

            """if self.powerPos >= self.maxPowerPos * self.frequency:  # Counter reset
                GPIO.output(self.resetPin, self.syncReset)
                self.syncState = not self.syncReset
                self.powerPos = 0"""

            time.sleep((1.0 / self.frequency) / 5.0 * 4)

            self.writeLine([1]*14)

            time.sleep((1.0 / self.frequency) / 5.0)

    def initGPIO(self):
        GPIO.setup(self.pinList, GPIO.OUT)
        GPIO.setup(self.resetPin, GPIO.OUT)
        GPIO.setup(self.syncPin, GPIO.OUT)

    def writeLine(self, line):
        GPIO.output(self.pinList, tuple(line))
