import serial

# Replace with your Arduino's serial port
arduino_port = '/dev/ttyACM0'

# Open serial port
ser = serial.Serial(arduino_port, 115200, timeout=1)

expect_persons = False
expect_distance = False

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print("Received:", line)  # Print the raw data received from Arduino
        
        # Parse your data and extract number of persons and their distances
        if line.startswith("The parameters of human body signs are:"):
            # Extract the number of persons
            num_persons = int(line.split(":")[-1].strip())
            print(f"Number of persons detected: {num_persons}")
            expect_persons = True
            expect_distance = False
        
        elif line.startswith("The sensor judges the distance to the human body to be:"):
            # Extract the distance
            distance = float(line.split(":")[-1].strip().split()[0])
            print(f"Distance to the person: {distance} meters")
            expect_distance = True
            expect_persons = False
        
        # Only print once both data have been received
        if expect_persons and expect_distance:
            print(f"Number of persons: {num_persons}, Distance: {distance} meters")
            expect_persons = False
            expect_distance = False

