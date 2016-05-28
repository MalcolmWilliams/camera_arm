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

def get_position(ser):
    ser.write("M114\n")
    #ser.readline()
    #print position
    position = ser.readline()
    print position
    ser.readline()

def motors_off(ser):
    ser.write("M18\n")
    ser.readline()

ser = serial.Serial()
startSerial(ser, "/dev/ttyACM0")

time.sleep(1.5)

ser.readline()
home(ser)
#ser.write("M18\n")
get_position(ser)
goto(ser,[80, 360, 1540])
get_position(ser)
