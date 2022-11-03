"""
Python script
"""

import serial
# import pandas as pd
from pynput import keyboard

COMPORT = "/dev/ttyACM0"  # Arduino port on Brooke's Ubuntu install
BAUDRATE = 9600  # Set baud rate for serial connection

# open the serial port
serialPort = serial.Serial(COMPORT, BAUDRATE, timeout=1)

def on_press(key):
    """
    Keyboard listener to command Arduino

    Args:
        key (Key): key that has been pressed

    Returns:
        Key | False
    """
    if key == keyboard.Key.esc:
        serialPort.write(bytes('stop', 'utf-8'))
        return False  # stop listener
    try:
        k = key.char  # single-char keys
    except:
        k = key.name  # other keys
    if k in ['space', 'up', 'down', '0', '1', '2', '3', '4', '5']:  # keys of interest
        # Send command to Arduino
        serialPort.write(bytes(k, 'utf-8'))

# Start keyboard listener
listener = keyboard.Listener(on_press=on_press)
listener.start()  # start to listen on a separate thread

while listener.is_alive:
    print("")