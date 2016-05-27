import serial
import time

def startSerial(ser, port):
    ser.baudrate = 115200
    ser.port = port
    ser.timeout = 20
    ser.open()
    ser.flushInput()
    print "Serial Settings: " + str(ser)
    print "Prepared To Start Communication"

def home(ser):  
    ser.write("G0 X0\n")
    ser.readline();


ser = serial.Serial()
startSerial(ser, "/dev/ttyACM0")

time.sleep(3.5)

home(ser)
