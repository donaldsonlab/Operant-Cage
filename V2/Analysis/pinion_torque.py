"""
This file plots the torque vs. linear acceleration relation for the Operant door. It is set up as a function that reads in a .csv file with the following name and value pairs:
    radius_pin [mm]   - radius of rotation of the pinion
    assem_mass [kg]   - mass of assembly being moved
    max_torque [kg*m] - stalling torque of the servo
    friction   []     - coefficient of friction
"""
# Imports
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt

def import_vals(filename = None):
    # This function imports the csv file of values and returns a corresponding dictionary.

    # Read csv into a dataframe
    constants = pd.read_csv(filename, header=None) # csv must not contain a header

    # Load into a dictionary
    constants = dict(zip(constants[0],constants[1]))

    return constants

def plot_func():
    # This function plots all the necessary equations and values.

    pass

def main():
    # Main logic and analysis

    pass