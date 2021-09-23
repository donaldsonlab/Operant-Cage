""" 
Date Created : 9/9/2021
Date Modified: 9/23/2021
Author: Ryan Cameron, David Protter, Sarah ???
Description: This script is for post-processing the csv file that bonsai outputs for the fiber photometry. The purpose of this is to put the names of the events back into the data file that bonsai outputs.
Property of Donaldson Lab, University of Colorado Boulder, PI Zoe Donaldson
http://www.zdonaldsonlab.com/
Code located at - https://github.com/donaldsonlab/Operant-Cage 
"""
# Imports
import numpy as np
import pandas as pd
import time as tm
import datetime as dt
import sys

# Parser
# Outline the mapping that is being used
commPath = 'RPI_operant//home_base//bonsai_commands.csv'
try: 
    f = open(commPath)
    print('File Opened...')
    f.close()
except:
    print('Command file does not exist...')
    sys.exit()

# Open the file and import the data
comms = pd.read_csv(commPath) # this is a pandas dataframe
pulses = list(comms.loc[:]['pulse length (ms)'])

# For each numeric value that is tagged correlate it to an event
dataFile = 'Software//Bonsai-Out//data.csv'
outputFile = 'Software//Bonsai-Out//finalData.csv'
data = pd.read_csv(dataFile)
vals = data.loc[:]['Value']
times = data.loc[:]['Timestamp']
newNames = []
newTimes = []
for iVal in range(len(vals)): # Loop through each value
    # Get individual Values
    val = vals[iVal]
    time = times[iVal]

    # Create Event Name
    index = pulses.index(val) # Find the index of the value
    name = comms.loc[index]['command'] # Get the command name

    # Create time since start of day in milliseconds
    time = time.split('T') # Splits the date and the time
    date = time[0]
    time = time[1] # Get the time with utc offset
    utcOff = "-" + time.split('-')[1]
    time = time.split('-')[0]
    # Convert the time to a time vector
    timeVec = time.split(':')
    # Convert to milliseconds
    timeVec = list(map(float, timeVec))
    timeVec[0] = timeVec[0]*60*60*1000
    timeVec[1] = timeVec[1]*60*1000
    timeVec[2] = timeVec[2]*1000
    time = sum(timeVec)

    # Replace the number with the name
    newNames.append(name)
    newTimes.append(time)

# Save the file
data.loc[:, 'Value'] = newNames
data['Time in ms'] = newTimes
data.to_csv(outputFile, index = False)