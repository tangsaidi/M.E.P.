import RPi.GPIO as GPIO
import time
import os

GPIO.setmode(GPIO.BCM)

GPIO.setup(26, GPIO.IN, pull_up_down = GPIO.PUD_UP)

bashCommand = "fswebcam -S 15 -r 640*420 --jpeg 85 -D 1 --save pic%Y-%m-%d_%H:%M:%s.jpg"

while True:
    input_state = GPIO.input(26)
    if input_state == False:
        os.chdir("/home/pi/Desktop/image")
        exitcode = os.system(bashCommand)
        time.sleep(0.2)
        
