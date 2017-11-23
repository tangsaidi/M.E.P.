# This serial reads serial input from Arduino
# If the Arduino sends char 't', server sends back a response with the real time
# If the Arduino sends char 'w' or anything other than 't', server sends back a 
# response with the weather info from weather.com

import serial
import pywapi
import time
from datetime import datetime

### Note: This file is in Python2

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
time.sleep(1.8)
while True:
    # Determine whether there is a serial input available from the serial monitor 
    while ser.inWaiting():
        if ser.read() == 't':
            # calls datetime object to get the time 
            current_time = (str) (datetime.now())
            current_time = current_time.translate(None, '-. :')
            current_time = current_time[0:14]
            ser.write(current_time.encode('utf-8'))
        else:
            # get the weather information from UWaterloo weather station using pywapi
            weather_response = pywapi.get_weather_from_weather_com('CAXX0531')
            print(weather_response['current_conditions']['text'])
            ser.write(weather_response['current_conditions']['text'].encode('utf-8'))
ser.close();

