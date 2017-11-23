import serial
import pywapi
import time
from datetime import datetime

### Note: This file is in Python2

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
time.sleep(1.8)
while ser.inWaiting():
    if ser.readline() == 't':
        current_time = (str) (datetime.now())
        ser.write(current_time[0:19])
    if ser.readline() == 'w':
        weather_response = pywapi.get_weather_from_weather_com('CAXX0531')
        ser.write(weather_response['current_conditions']['text'])


##current_time = (str) (datetime.now())
##
##weather_response = pywapi.get_weather_from_weather_com('CAXX0531')
##print(weather_response['current_conditions']['text'])
##print(current_time[0:19])
