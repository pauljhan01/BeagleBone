import serial

ser = serial.Serial()
ser.baudrate = 115200
ser.port = '/dev/ttyS4'
ser.timeout = 0.5
ser.open()
print(ser)
ser.write(b'hello')
ser.close()
