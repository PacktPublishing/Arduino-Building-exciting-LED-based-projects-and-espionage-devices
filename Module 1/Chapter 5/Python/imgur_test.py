import pyimgur # imgur library
import urllib  # url fetching default library
import time    # time library to add delay like in Arduino

CLIENT_ID = "50e8d92be50757f" # imgur client ID

# retrieve the snapshot from the camera and save it as an image in the chosen directory
urllib.urlretrieve("http://192.168.0.111:81/snapshot.cgi?user=admin&pwd=password", "mug_shot.jpg")
time.sleep(2)           
PATH = "C:\\helloworld\\mug_shot.jpg" # location where the image is saved
 
im = pyimgur.Imgur(CLIENT_ID) # authenticates into the imgur platform using the client ID
uploaded_image = im.upload_image(PATH, title="Uploaded with PyImgur") # uploads the image privately
print(uploaded_image.link) # fetches the link of the image URL