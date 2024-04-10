import inputs
import serial
import random
import time

#import string

def read_gamepad():
    # Open the serial port
    nCom = 6 #input("Escriba el número del puerto COM en el que se encuentra el Arduino: ")
    serialPort = serial.Serial(f"COM{nCom}", 115200)  # Replace 'COM1' with the appropriate port name.

    maximop = 32767
    minimop = -32768
    cero = 0

    codigo = 'RX'

    while True:

        serialPort.write(codigo.encode()) #revisar endianness de envío de letras
        serialPort.write(maximop.to_bytes(2, byteorder='little', signed=True))
        time.sleep(1)

        serialPort.write(codigo.encode()) #revisar endianness de envío de letras
        serialPort.write(minimop.to_bytes(2, byteorder='little', signed=True))
        time.sleep(1)

        serialPort.write(codigo.encode()) #revisar endianness de envío de letras
        serialPort.write(maximop.to_bytes(2, byteorder='little', signed=True))
        time.sleep(1)

        serialPort.write(codigo.encode()) #revisar endianness de envío de letras
        serialPort.write(minimop.to_bytes(2, byteorder='little', signed=True))
        time.sleep(1)

        serialPort.write(codigo.encode()) #revisar endianness de envío de letras
        serialPort.write(cero.to_bytes(2, byteorder='little', signed=True))

        #time.sleep(0)          

 

        """gamepads = inputs.devices.gamepads
        if gamepads:
            events = inputs.get_gamepad()
            data = ""
            for event in events:
                # Convert the event data to a string
                if event.code != 'SYN_REPORT':
                    key = event.code
                    state = int(event.state)
                    code = {'ABS_Z': 'LT', 'ABS_RZ': 'RT', 
                            'BTN_TL': 'LB', 'BTN_TR': 'RB', 
                            'ABS_HAT0X': 'GX', 'ABS_HAT0Y': 'GY',
                            'BTN_START': 'LC', 'BTN_SELECT': 'RC',
                            'BTN_WEST': 'BX', 'BTN_NORTH': 'BY',
                            'BTN_SOUTH': 'BA', 'BTN_EAST': 'BB',
                            'ABS_X': 'LX', 'ABS_Y': 'LY',
                            'ABS_RX': 'RX', 'ABS_RY': 'RY',
                            'BTN_THUMBL': 'LJ', 'BTN_THUMBR': 'RJ'}
                    data = f"{code[key]}"
                    serialPort.write(data.encode()) #revisar endianness de envío de letras
                    serialPort.write(state.to_bytes(2, byteorder='little', signed=True))
                    print(data, state)

                    #for i in range(0, 1000000):
                    #    pass

                    #read = serialPort.readable()
                    #if read: 
                    #    message = serialPort.read(min(20, serialPort.in_waiting))
                    #    print("Recibido:", message)"""

if __name__ == "__main__":
    read_gamepad()