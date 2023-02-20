import cv2
# had to use legacy for some trackers 
# install opencv-contrib-python 
# pip install opencv-contrib-python -U
import imutils
# pip install imutils

TrDict = {'csrt': cv2.TrackerCSRT_create,
          'kcf': cv2.TrackerKCF_create,
          'boosting': cv2.legacy.TrackerBoosting_create,
          'mil': cv2.TrackerMIL_create,
          'tld': cv2.legacy.TrackerTLD_create,
          'medianflow': cv2.legacy.TrackerMedianFlow_create,
          'mosse': cv2.legacy.TrackerMOSSE_create}

tracker = TrDict['csrt']()

# or to call the tracker directly
# tracker = cv2.TrackerCSRT_create()

# Read video
# video = cv2.VideoCapture(r'C:\Users\Tinho\Documents\python_scripts\mot.mp4')
# read webcam
video = cv2.VideoCapture(0)

# read and show first frame
ret, frame = video.read()
# resize frame
frame = imutils.resize(frame, width=600)
cv2.imshow("Frame", frame)
bb = cv2.selectROI("Frame", frame)
print(bb)

# initialize tracker
tracker.init(frame, bb)

while True:
    # read the next frame, if there is frame ret returns true
    ret, frame = video.read()
    # resize frame
    frame = imutils.resize(frame, width=600)
    # if the frame is None, we have reached the end of the stream
    if not ret:
        break
    
    # update tracker on new frame
    success, bb = tracker.update(frame)
    # draw bounding box
    (x, y, w, h) = [int(v) for v in bb]
    # draw bounding box on frame, (0, 255, 0) is color, 2 is thickness
    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
    # show frame with bounding box
    cv2.imshow("Frame", frame)
    # quit if q is pressed
    
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

# close video
video.release()
# close all windows
cv2.destroyAllWindows()

