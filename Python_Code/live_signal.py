import pandas as pd
import serial
import numpy as np
import time
from os import system
from sklearn.ensemble import RandomForestClassifier
import pickle5 as pickle
import win32com.client as wincl
speak = wincl.Dispatch("SAPI.spVoice")

clf_rf = pickle.load(open('word_model1','rb'))
serial_port = '/dev/ttyS6';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
#write_to_file_path = "test_df.csv";

def sound_function(predictions):
    system('say %s' %(predictions))

def countloop():
    #output_file = open(write_to_file_path, "w+");   # For saving the predicted value in file for later use
    arduino = serial.Serial('COM5', baud_rate)
    count=0;
    while True:

        arduino.flush() # clears the arduino buffer memory
        line=arduino.read(arduino.inWaiting())   # reading inputs from arduino interface
        line=line.decode("utf-8")    # decooding the inputs from arduino
        print(line);
        line_split = line.split(',')[0:11]
        if count>3:
            #print(line_split)
            flag=0
            #print("file is reading")
            #print(line_split[10].)
            for el in line_split:
                if el =='':
                    #print(el)
                    flag=1
            if len(line_split)!=11:
                    flag=1
            #print(flag)
            if flag==0:
                prediction = clf_rf.predict([line_split])
                print("the prediction for the Sign is")
                print(prediction[0])
                speak.speak(prediction[0])
            time.sleep(1)    # delaying the loop so that system takes input per second
        count = count + 1

countloop()
