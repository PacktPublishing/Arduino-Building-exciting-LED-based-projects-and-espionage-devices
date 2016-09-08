import serial
import pyimgur
import urllib
import time
from pushover import init, Client
         
print("Burglar Alarm Program Initializing")   
init("azhGtg6JmozL2HHZiAwje9KJYEJFDJ")       
CLIENT_ID = "50e8d92be50757f"
PATH = "C:\\helloworld\\mug_shot.jpg"
im = pyimgur.Imgur(CLIENT_ID)
mug_shot_ctr = 0
serial_status = 0
camera_status = 0

try:
    print("\nAttempting to connect to Bluetooth module...")
    ser = serial.Serial('COM36', 9600) #Tried with and without the last 3 parameters, and also at 1Mbps, same happens.
    time.sleep(3)
    serial_status = 1
    print('Bluetooth connection successful!')
except:
    print('Bluetooth Connection Error! \nPlease check if bluetooth is connected.')
    mug_shot_ctr = 4

try:
    print("\nChecking IP Camera Status...")
    urllib.urlretrieve("http://192.168.0.105:81/snapshot.cgi?user=admin&pwd=password", "mug_shot.jpg")
    time.sleep(2)
    print("Camera Status OK")
    camera_status = 1
except:
    print("Camera not connected!\nPlease check if camera is connected.")
    mug_shot_ctr = 4

if((serial_status==1)&(camera_status==1)):
    print("\nBurglar Alarm armed!")
    
while mug_shot_ctr < 3:
    line = ser.readline()
    if(line[0]=='1'):
        print('\nMotion Detected!')
        print('Capturing Mug Shot')
        urllib.urlretrieve("http://192.168.0.105:81/snapshot.cgi?user=admin&pwd=password", "mug_shot.jpg")
        time.sleep(2)
        print('Uploading image to Imgur')
        uploaded_image = im.upload_image(PATH, title="Uploaded with PyImgur - Mugshot")
        print(uploaded_image.link)
        print('Sending notification to device.')
        Client("u6BdkLpT3i2pJMQVVvHrSBxn4eNaMq").send_message("Mug Shot: "+ uploaded_image.link, title="Intruder Alert!")
        print('Notification sent!')
        mug_shot_ctr = mug_shot_ctr + 1
if(serial_status ==1):
    ser.close()
    print('\nProgram Ended')
time.sleep(5)