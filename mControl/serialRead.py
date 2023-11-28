import serial
import time

# Establish serial communication
arduino = serial.Serial('COM9', 9600)
time.sleep(2)  

def get_machine_status():
    arduino.write(b"get_status\n")  # Send request for status
    time.sleep(0.1)  # Wait for response
    response = arduino.readline().decode().strip()
    return response


status = get_machine_status()
print(f"Machine status: {status}")

try:
    while True:
        if arduino.in_waiting > 0:
            message = arduino.readline().decode().strip()
            if message == "Image captured":
                capture_image()
                time.sleep(0.1)
                
except KeyboardInterrupt:
    pass

arduino.close()  # Close serial connection

