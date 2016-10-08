from clarifai.client import ClarifaiApi
from picamera import PiCamera
from time import sleep
from twilio.rest import TwilioRestClient
import datetime
import json
import os
import pprint
import serial
import sys
import time

arguments = sys.argv

try:
    ser = serial.Serial('/dev/ttyACM0', 9600)
except:
    ser = serial.Serial('/dev/ttyACM1', 9600)

client = TwilioRestClient(arguments[4], arguments[5])

while(True):
    temp = ser.readline()
    if(temp.startswith("Sound: ")):
        if(int(temp.replace("Sound: ", "").replace("\r\n", "")) >= 10000):
            h = open("whitelist.txt", "r")
            for line in h:
                
                message = client.messages.create(to=line, from_=arguments[3], body="It's a bit loud")

            h.close()

            sleep(60)
    
    if(temp.startswith("knocker: ")):
        if(temp.replace("knocker: ", "").replace("\r\n", "") == "1"):
            nom = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d_%H:%M:%S') + ".png"
            
            camera = PiCamera()
            camera.capture(nom)
            
            clarifai_api = ClarifaiApi(arguments[1], arguments[2])
            result = clarifai_api.tag_images(open('./' + nom, 'rb'))

            os.remove(nom)

            r = json.dumps(result)
            loaded = json.loads(r)

            tags = []

            j = open("importantTags.txt", "r")
            for line in j:
                if line.lower() in loaded['results'][0]['result']['tag']['classes']:
                    tags.append(line)
            j.close()
            
            g = open("whitelist.txt", "r")
            for line in g:
                message = client.messages.create(to=line, from_=arguments[3], body=("Someone is at the door! " + ', '.join(tags)))
            g.close()

            sleep(60)
            #sys.exit()
