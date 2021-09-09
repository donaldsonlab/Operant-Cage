""" 
Date Created : 9/9/2021
Date Modified: 9/9/2021
Author: Ryan Cameron, David Protter, Sarah ???
Description: This script is for post-processing the csv file that bonsai outputs for the fiber photometry. The purpose of this is to put the names of the events back into the data file that bonsai outputs.
Property of Donaldson Lab, University of Colorado Boulder, PI Zoe Donaldson
http://www.zdonaldsonlab.com/
Code located at - https://github.com/donaldsonlab/Operant-Cage 
"""
# Imports
import numpy as np
import pandas as pd
import time
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
data = pd.read_csv(dataFile)
vals = data.loc[:]['Value']
newNames = []
for iVal in range(len(vals)): # Loop through each value
    val = vals[iVal]
    index = pulses.index(val) # Find the index of the value
    name = comms.loc[index]['command'] # Get the command name
    # Replace the number with the name
    newNames.append(name)

# Save the file
data.loc[:, 'Value'] = newNames
data.to_csv(dataFile, index = False)