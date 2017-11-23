# ButtonTest.py uses two GPIO pins with a button to control the external web camera
# and stores the output image to the target folder of "detectChange"

import RPi.GPIO as GPIO
import time
import os

# Sets the status of button
GPIO.setmode(GPIO.BCM)
GPIO.setup(26, GPIO.IN, pull_up_down = GPIO.PUD_UP)

# Below is the bash command that uses fswebcam to take a jpeg photo with our web camera
# The output would be in the format of year-month-day_hour-minute-seconds.jpg 
bashCommand = "fswebcam -S 15 -r 640*420 --jpeg 85 -D 1 --save pic%Y-%m-%d_%H:%M:%s.jpg"

# Starts an infinite loop 
while True:
    input_state = GPIO.input(26)
    print(input_state)
    # Goes into the if statement if the switch closes
    if input_state == True:
        while True:
        	# Wait until the button opens again, then execute the bashcommand
        	# This is intended to model the open and closed state of a microwave oven door
            if GPIO.input(26) == False:
                break    
        os.chdir("/home/pi/Desktop/image")
        exitcode = os.system(bashCommand)
