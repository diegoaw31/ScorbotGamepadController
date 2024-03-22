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
                    data = f"{event.code} {event.state}\0"  # Add a newline character between each event's data, importante el \0
                    ser.write(data.encode())
                    print(data)
        else:
            print("No gamepad found.")

if __name__ == "__main__":
    read_gamepad()