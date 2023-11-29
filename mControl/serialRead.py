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

def capture_image():
    print("Image capture command sent to Arduino.")

i = 0
j = 0

try:
    while True:
        if arduino.in_waiting > 0:
            message = arduino.readline().decode().strip()
            if message.startswith("Image captured at i = "):
                # Extracting i and j values from the received message
                parts = message.split(", j = ")
                i_val = int(parts[0].split(" = ")[1])
                j_val = int(parts[1])
                print(f"Extracted values: i = {i_val}, j = {j_val}")
                i += 1
                j += 1
                time.sleep(0.1)  # Small delay to prevent repeated triggering
except KeyboardInterrupt:
    pass

arduino.close()  # Close serial connection
