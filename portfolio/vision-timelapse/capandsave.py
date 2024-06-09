import cv2
from PIL import Image, ImageDraw, ImageFont
import datetime
import time
import os
import glob
import keyboard

print("starting!!!")

# function to find the next file number
def next_file_number(pattern):
    # get a list of existing files
    files = glob.glob(pattern)
    numbers = [int(f.split('_')[1].split('.')[0]) for f in files]
    print("numbers: ", numbers)
    print("next number: ", max(numbers) + 1 if numbers else 1)
    return max(numbers) + 1 if numbers else 1

# main function to take snapshot
def take_snapshots(interval=5*60, quit_key='q'):
    # setup the webcam
    cap = cv2.VideoCapture(0)
    # check if the webcam is opened correctly
    if not cap.isOpened():
        print("Error opening webcam")
        return
    file_pattern = "image_*.jpg"
    

    try:
        while True:
            # read the image from the camera
            ret, frame = cap.read()
            if not ret:
                print("Error capturing image")
                break
            # convert image to PIL format
            image = Image.fromarray(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
            # get the current time
            timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            # add the timestamp to the image
            draw = ImageDraw.Draw(image)
            font = ImageFont.truetype("arial.ttf", 36)
            bbox = draw.textbbox((0, 0), text=timestamp, font=font)

            text_width, text_height = bbox[2] - bbox[0], bbox[3] - bbox[1]
            
            draw.text((image.width - text_width, image.height - text_height-10), timestamp, font=font,fill=(255, 255, 255))
            # save image with ascending number in filename
            file_number = next_file_number(file_pattern)
            image.save(f"image_{file_number:04d}.jpg")
            print(f"image_{file_number:04d}.jpg saved")
            # wait for the specified interval, seconds
            time.sleep(interval)
            # check if the quit key was pressed
            if keyboard.is_pressed(quit_key):
                break

    finally:
        # release the webcam
        cap.release()
        cv2.destroyAllWindows()

# call the main function
take_snapshots()



    