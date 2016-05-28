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
    ser.write("G28\n")
    ser.readline()

def goto(ser, pos):
    ser.write("G0 X"+str(pos[0])+" Y"+str(pos[1])+" Z"+str(pos[2])+"\n")
    ser.readline()

ser = serial.Serial()
startSerial(ser, "/dev/ttyACM0")

time.sleep(1.5)

home(ser)
#goto(ser,[80, 360, 540])
#ser.write("M18\n")
