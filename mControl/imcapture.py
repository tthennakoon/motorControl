# import libraries
import numpy as np
import cv2
import os
import time

# Create a directory to store frames
if not os.path.exists('frames'):
    os.makedirs('frames')

# Initialize variables
frame_count = 0
save_frames = False
start_time = time.time()

# Capture video from camera
capture_video = cv2.VideoCapture(1)

while True:
    ret, frame = capture_video.read()
    if ret:
        frame = cv2.flip(frame, 1)
        cv2.imshow('frame', frame)

        # Check for key press
        key = cv2.waitKey(1) & 0xFF
        if key == ord('c'):
            save_frames = True
        elif key == ord('s'):
            break

        # Save frames if enabled
        if save_frames and time.time() - start_time >= 1:
            frame_count += 1
            filename = f'frames/frame_{frame_count}.jpg'
            cv2.imwrite(filename, frame)
            print(f'Saved frame {frame_count}')
            start_time = time.time()

    else:
        break

# Release video capture and destroy windows
capture_video.release()
cv2.destroyAllWindows()