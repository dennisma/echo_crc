import serial
import time
from ucSerialComm import ucComm

pico = ucComm()
pico.send("All work and no play makes Dennis a Dull Boy!!!")
while(True):
    if pico.msgWaiting():
        #time.sleep(0.01)
        success,sentence = pico.read()
        #print (success, sentence)
        if success:
            pico.send(sentence)
        else:
            print("unsuccessful read... break")
            break


print ('done')