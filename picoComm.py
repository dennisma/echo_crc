
import serial
import time


def checksum(sentence):
    calc_cksum = 0
    for s in sentence:
        calc_cksum ^= ord(s)

    """ Return the nmeadata, the checksum from
        sentence, and the calculated checksum
    """
    return calc_cksum


class ucComm:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyAMA0', 9600) 

    def send(self,value):
        cs = checksum(value)
        value += '*'+str(cs)+'\n'
        self.ser.write(value.encode('ascii'))

    def msgWaiting(self):
        return self.ser.in_waiting > 0
    # return msg
    def read(self):
        value = ""
        success = True
        while self.msgWaiting():
            try:
                data = self.ser.readline().decode()
                l = data[:-1].split('*')
                value = l[0]
                crc = int(l[1])
                calccrc =checksum(value)
                success= (calccrc == crc)
            except:
                success = False
                value = ""
                break
        return (success,value)


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
