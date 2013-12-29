import serial

def read_serial(device='/dev/ttyUSB0', speed="115200", func=lambda x: print(x)):
    serial_device = serial.Serial(device, speed)
    while True:
        line = serial_device.readline()
        func(str(line))

    serial_device.close()

if __name__ == "__main__":
    read_serial()