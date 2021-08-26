# This script extends the lever out and reads the value that the lever needs to be extended at

# Imports
import os
os.environ['DISPLAY']=':0.0'
from pynput.keyboard import Listener, Key

def on_press(key):
    print("Key pressed: {0}".format(key))

def on_release(key):
    print("Key released: {0}".format(key))

with Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join() 