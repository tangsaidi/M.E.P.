from base64 import b64encode
from os import makedirs
from os.path import join, basename
from sys import argv
import json
import requests

myAPIKey = 'AIzaSyC-SHS_56ZC7GC3dv374UcGsOUD3PTLEtQ'
ENDPOINT_URL = 'https://vision.googleapis.com/v1/images:annotate'
RESULTS_DIR = 'jsons'
makedirs(RESULTS_DIR, exist_ok=True)

def make_image_data_list(image_filenames):
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
            """appending the imgrequest list to meet google api requirement"""
            # img_requests.append({
            #         'image': {'content': ctxt},
            #         'features': [{
            #             'type': 'TEXT_DETECTION',
            #             'maxResults': 1
            #         }]
            # })
            img_requests.append({
                    'image': {
                        'content': ctxt},
                    'features':[{
                        'type':'LABEL_DETECTION'
                    }] 
            
            })

    return img_requests

def make_image_data(image_filenames):
    """Returns the image data lists as bytes"""
    imgdict = make_image_data_list(image_filenames)
    return json.dumps({"requests": imgdict }).encode()


def request_ocr(api_key, image_filenames):
    response = requests.post(ENDPOINT_URL,
                             data=make_image_data(image_filenames),
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
        response = request_ocr(myAPIKey, image_filenames)
        if response.status_code != 200 or response.json().get('error'):
            print(response.text)
        else:
            for idx, resp in enumerate(response.json()['responses']):
                # save to JSON file
                imgname = image_filenames[idx]
                jpath = join(RESULTS_DIR, basename(imgname) + '.json')
                with open(jpath, 'w') as f:
                    datatxt = json.dumps(resp, indent=2)
                    print("Wrote", len(datatxt), "bytes to", jpath)
                    f.write(datatxt)

                # print the plaintext to screen for convenience
                print("---------------------------------------------")
                # t = resp['textAnnotations'][0]
                # print("    Bounding Polygon:")
                # print(t['boundingPoly'])
                # print("    Text:")
                # print(t['description'])
                for i in range (0, 3):
                    t = resp['labelAnnotations'][i]
                    print("Description:          ")
                    print(t['description'])
                    print("Confidence:       ")
                    print(t['score'])
                    i = i + 1




