from clarifai.client import ClarifaiApi
clarifai_api = ClarifaiApi()
print(clarifai_api.tag_image_urls('https://samples.clarifai.com/metro-north.jpg')) 
print(clarifai_api.color_urls('https://samples.clarifai.com/metro-north.jpg'))
