import inputs
import serial

#import string

def read_gamepad():
    # Open the serial port
    ser = serial.Serial('COM7', 115200)  # Replace 'COM1' with the appropriate port name

    while True:
        gamepads = inputs.devices.gamepads
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
                    ser.write(data.encode())
                    ser.write(state.to_bytes(2, byteorder='big', signed=True))
                    print(data, state)
        else:
            print("No gamepad found.")

if __name__ == "__main__":
    read_gamepad()