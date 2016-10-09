import config
import requests
import json
import base64

headers = {
  'Content-Type': 'application/json',
  'app_id': config.kairosAppId,
  'app_key': config.kairosKey
}

def enrollJoe():
  with open('./pics/joe.jpg', 'rb') as image:
    encoded_image = base64.b64encode(image.read())
  payload = {
    'image': encoded_image,
    'subject_id': 'joeSweeney',
    'gallery_name': 'hackUmass2016'
  }
  res = requests.post('http://api.kairos.com/enroll', data=json.dumps(payload), headers=headers)
  print(res.text)

  with open('./pics/joe2.jpg', 'rb') as image:
    encoded_image = base64.b64encode(image.read())
  payload = {
    'image': encoded_image,
    'subject_id': 'joeSweeney',
    'gallery_name': 'hackUmass2016'
  }
  res = requests.post('http://api.kairos.com/enroll', data=json.dumps(payload), headers=headers)
  print(res.text + '\n')

  with open('./pics/joe5.jpg', 'rb') as image:
    encoded_image = base64.b64encode(image.read())
  payload = {
    'image': encoded_image,
    'subject_id': 'joeSweeney',
    'gallery_name': 'hackUmass2016'
  }
  res = requests.post('http://api.kairos.com/enroll', data=json.dumps(payload), headers=headers)
  print(res.text + '\n')

def removeJoe():
  payload = {
    'gallery_name': 'hackUmass2016',
    'subject_id': 'joeSweeney'
  }
  res = requests.post('http://api.kairos.com/gallery/remove_subject', data=json.dumps(payload), headers=headers)
  print(res.text)

def testJoe():
  with open('./pics/test_joe.jpg', 'rb') as image:
      encoded_image = base64.b64encode(image.read())
  payload = {
    'image': encoded_image,
    'gallery_name': 'hackUmass2016'
  }
  res = requests.post('http://api.kairos.com/recognize', data=json.dumps(payload), headers=headers)
  print(res.text + '\n')

  with open('./pics/test_joe2.jpg', 'rb') as image:
      encoded_image = base64.b64encode(image.read())
  payload = {
    'image': encoded_image,
    'gallery_name': 'hackUmass2016'
  }
  res = requests.post('http://api.kairos.com/recognize', data=json.dumps(payload), headers=headers)
  print(res.text)

# enrollJoe()
testJoe()