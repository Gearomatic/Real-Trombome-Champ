import serial
import time
import mouse

serialcomm = serial.Serial('COM6', 9600, timeout = 1)
serialcomm.reset_input_buffer()

while True:
    if serialcomm.in_waiting > 0:
        line = serialcomm.readline().decode('utf-8').rstrip()
        print(line)
        mouse.move("200", line)
