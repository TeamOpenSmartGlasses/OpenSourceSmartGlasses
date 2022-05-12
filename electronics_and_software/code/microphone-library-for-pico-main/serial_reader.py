import serial

mic_num = 4
mics_input_counts = [0] * 4

with serial.Serial('/dev/ttyACM0', 115200, timeout=3) as ser:
    while True:
        try:
            line = ser.readline().decode("utf-8") # read a '\n' terminated line
            str_find = "id: "
            print(line)
            pos = line.find(str_find)
            if pos != -1:
                curr_mic_id = int(line[pos+len(str_find):])
                mics_input_counts[curr_mic_id] += 1
        except serial.serialutil.SerialException as e:
            print(e)
            print("Exiting loop")
            break

print(mics_input_counts)
