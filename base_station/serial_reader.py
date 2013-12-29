import serial

def read_serial(device='/dev/ttyUSB0', speed="115200", func=lambda x: print(x)):
    serial_device = serial.Serial(device, speed)
    for line in serial_device.readline():
        func(line)

    serial_device.close()

if __name__ == "__main__":
    read_serial()