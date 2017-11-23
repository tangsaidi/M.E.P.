import serial
import pywapi
import time
from datetime import datetime

### Note: This file is in Python2

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
time.sleep(1.8)
while True:
    while ser.inWaiting():
        if ser.read() == 't':
            current_time = (str) (datetime.now())
            current_time = current_time.translate(None, '-. :')
            current_time = current_time[0:14]
            ser.write(current_time.encode('utf-8'))
        else:
            weather_response = pywapi.get_weather_from_weather_com('CAXX0531')
            print(weather_response['current_conditions']['text'])
            ser.write(weather_response['current_conditions']['text'].encode('utf-8'))
ser.close();

##current_time = (str) (datetime.now())
##current_time = current_time.translate(None, '-. :')
##weather_response = pywapi.get_weather_from_weather_com('CAXX0531')
##print(weather_response['current_conditions']['text'])
##print(current_time[0:14])

