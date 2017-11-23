
from base64 import b64encode
from os import makedirs
from os.path import join, basename
from sys import argv
import json
import requests
import math
import serial
import time

from fuzzywuzzy import fuzz
from fuzzywuzzy import process

###
### This code is written in Python 3
###

myAPIKey = 'AIzaSyC-SHS_56ZC7GC3dv374UcGsOUD3PTLEtQ'
ENDPOINT_URL = 'https://vision.googleapis.com/v1/images:annotate'
RESULTS_DIR = 'jsons'
makedirs(RESULTS_DIR, exist_ok=True)
foodtime = 45
first_string = ""
second_string = ""
def make_image_data_list(image_filenames, content_type):
    """
    image_filenames is a list of filename strings
    Returns a list of dicts formatted as the Vision API
        needs them to be
    """
    img_requests = []
    for imgname in image_filenames:
        """read the imgname as binary"""
        with open(imgname, 'rb') as f:
            ctxt = b64encode(f.read()).decode()
            img_requests.append({
                    'image': {
                        'content': ctxt},
                    'features':[{
                        'type': content_type
                    }] 
            
            })

    return img_requests

def make_image_data(image_filenames, content_type):
    """Returns the image data lists as bytes"""
    imgdict = make_image_data_list(image_filenames, content_type)
    return json.dumps({"requests": imgdict }).encode()


def request_label(api_key, image_file):
    response = requests.post(ENDPOINT_URL,
                             data=make_image_data(image_filenames, 'LABEL_DETECTION'),
                             params={'key': myAPIKey},
                             headers={'Content-Type': 'application/json'})
    return response

#detect size of the dominant pixels

def request_size(api_key, image_filenames):
    response = requests.post(ENDPOINT_URL,
                            data= make_image_data(image_filenames, 'IMAGE_PROPERTIES'),
                            params={'key': myAPIKey},
                            headers={'Content-Type': 'application/json'})
    return response


if __name__ == '__main__':

    image_filenames = argv[1:]
    if not image_filenames:
        print("""
            Please supply an api key, then one or more image filenames
            $ python cloudvisreq.py api_key image1.jpg image2.png""")
    else:
        response = request_label(myAPIKey, image_filenames)
        sizeresponse = request_size(myAPIKey, image_filenames)
        if response.status_code != 200 or response.json().get('error'):
            print(response.text)
        else:
            for idx, resp in enumerate(response.json()['responses']):
                # save to JSON file
                imgname = image_filenames[idx]
                jpath = join(RESULTS_DIR, basename(imgname) + '.json')
                with open(jpath, 'w') as f:
                    datatxt = json.dumps(resp, indent=2)
                    # print("Wrote", len(datatxt), "bytes to", jpath)
                    f.write(datatxt)


                keys = ['milk','spaghetti','ramen','steak','drink','bread','potato','barbecue','wings','burrito','pasta','pizza','vegetable','burger','hot dog','chicken','fish', 'rice']
                values = [40, 90, 80, 140, 40, 40, 70, 140, 115, 85, 90, 75, 50, 105, 115, 85, 120, 90]
                items = {k:v for k, v in zip(keys, values)}

                # print the plaintext to screen for convenience
                i = len(resp['labelAnnotations']) - 1;
                bestmatch = "dish"
                while (i >= 0):
                    t = resp['labelAnnotations'][i]
                    result = process.extractOne(t['description'], keys)
                    if result[1] >= 70:
                        bestmatch = result[0]
                    i = i - 1
                # print("They are ")
                first_string = bestmatch + ";"
                # print("time is")
                if bestmatch != "dish":
                    foodtime = items[bestmatch]
                else:
            	    foodtime = 80
            #save the size response to a size.json file
            for idx, resp in enumerate(sizeresponse.json()['responses']):
                # save to JSON file
                imgname = image_filenames[idx]
                jpath = join(RESULTS_DIR, basename(imgname) + 'size' + '.json')
                with open(jpath, 'w') as f:
                    datatxt = json.dumps(resp, indent=2)
                    # print("Wrote", len(datatxt), "bytes to", jpath)
                    f.write(datatxt)
                t = resp['cropHintsAnnotation']['cropHints'][0]["boundingPoly"]['vertices']
                area = int(t[1]['x']) * int(t[3]['y']) * 0.0007
                volume = area * math.sqrt(area)
                second_string = str(int(volume*0.0001*foodtime))

                
                final_string = first_string+second_string
                if (bestmatch!= "dish"):
                    with serial.Serial('/dev/ttyACM0',9600, timeout = 5) as ser:
                        time.sleep(1.8)
                        ser.write(final_string.encode('utf-8'))

                print(first_string + second_string)


