import numpy as np
from Letters import letters

def hexToBin(a):
    return list(bin(a)[2:].zfill(7))[::-1]

def charToBinMatrix(a):
    e = np.array(map(hexToBin, a))
    e = np.concatenate((e, np.zeros((1, 7)).astype(int)))
    return e

def textToBinMatrix(text):
    if len(text) == 0:
        return None
    text = [letters[ord(x)-32] for x in text]
    tmpArray = charToBinMatrix(text[0])
    for i in range(1, len(text)):
        tmpArray = np.concatenate((tmpArray, charToBinMatrix(text[i])), 0).astype(int)

    return tmpArray.astype(int)