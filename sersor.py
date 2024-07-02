import serial

# Replace with your Arduino's serial port
arduino_port = '/dev/ttyACM0'

# Open serial port
ser = serial.Serial(arduino_port, 115200, timeout=1)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
      #  print("Received:", line)  # Print the raw data received from Arduino
        
        # Parse your data and extract number of persons and their distances
        if line.startswith("The parameters of human body signs are:"):
            # Extract the number of persons
            num_persons = int(line.split(":")[-1].strip())
            print(f"Number of persons detected: {num_persons}")
        
       # if line.startswith("The sensor judges the distance to the human body to be:"):
            # Extract the distance
           # distance = float(line.split(":")[-1].strip().split()[0])
           # print(f"Distance to the person: {distance} meters")

