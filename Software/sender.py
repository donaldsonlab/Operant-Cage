# This is the object that will send data to the arduino and converely to Bonsai

import serial as ser
import time
#import RPi.GPIO as gpio 
import pandas as pd

class sender:
    # SENDER is the object that sends information to Bonsai which includes timestamps and information on what event has occured. The arduino will take the serial commands and turn them into the correct signals for Bonsai.

    def __init__(self, port = None, baud = 9600, commandFile = 'Software/commands.csv'):
        self.port = port
        self.baudRate = baud
        self.data = None

        # Initialize the port
        self.ser = ser.Serial(self.port, self.baudRate)
        self.commands = self.get_commands(commandFile)

    def send_data(self):
        # SEND_DATA sends the timestamp and command to the arduino itself
        formatted = self.data + "\r"
        formatted = formatted.encode('ascii')
        self.ser.write(formatted)

    def get_data(self, command):
        # GET_DATA gets the data needed from the associated software, in form of a command string. The command must match one of the possible command sequences outlined in the commands.csv file

        # Search for the command in the list of possible commands
        try:
            description = self.commands[command]
        except ValueError:
            print('Not a valid command')
            return 
        
        self.data = command
    
    def get_commands(self, fileName):
        # GET_COMMANDS gets the list of possible command names from a previously defined file

        commDict = pd.read_csv(fileName, index_col=0, header = None, squeeze=True).to_dict()
        return commDict

# Test some stuff
obj = sender()
obj.get_data('leverOutFood')
print(obj.commands)

