README

### Microwave Empowerment Project (M.E.P.)

Our SE101 project intends to bring the modern microwave oven to a completely new level.
We gave it ability to not only recognize your delicacy, but also recommend a time based
on the what that dish is, how large is the portion, how cold is the food. With our 
sophisticated algorithms, you don't need to worry about the time. All you need to do
is putting your food in our enhanced microwave. Our microwave will count down the time 
and tell you when your feast is ready. We aim to deliver the best customer
experience in the kitchenware industry.

However, if you feel like modifying the time based on your personal preferences with 
our unique gestures recognition feature. Swipe right if you prefer medium well! Swipe
left if you prefer to have it rare.

Last but definitely not the least, customer safety is our first priority. According to
National Fire Protection Association's research, an average of astonishing around 7300
home structure fire per year. These fires annually cause 10 deaths and nearly 200 
injuries, not mentioning the direct property damage. Metal containers and foils are the
most prominent causes of these accidents. Therefore, we implemented metal detection 
functionality to prevent these tragedies from happening. As soon as, your metal container
enters the microwave, a buzzer will ring as a warning. DO NOT IGNORE THIS! In order to
keep our safety system robust even when the main controller is down, we built it on an
independent control system.

CHEERS FOR THE BRIGHT FUTURE OF MICROWAVES!!!


*Additional Features:
1. Current time
2. The weather outside
3. Various greeting messages at different time of a day


# Instructions:

Server/FINAL contains all the server side code. 
1. start.sh: Starts all three background processes, including detectChange, SerialHandler
   and ButtonTest
2. detectChange: this shell script monitors the activities within a folder. If an image
   is added, it triggers the VisionRequest.py

Arduino/Arduino_Main includes all the implentaion of features such as gestures recognition,
LED screen control, serial input processing.

Arduino/Metal_Detector2.0 implements improved version of metal detection algorithm. This
code runs on an independent Arduino board. 

For more detailed explanations, please go into each source code file.


# Languages used:
Demo:
1. Arduino (C/C++)
2. Python2 (ButtonTest.py & SerialHandler.py)
3. Python3 (VisionRequest.py)
4. Bash Script

# Prototype:
4. Processing
5. Automator



