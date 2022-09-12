import asyncio
import time
import websockets
import base64
import pyaudio
import sys

audio_buffer = b''
i = 0
times_since_last = list()
last_time = -1
            
           
f = open('./curr_audio.raw', 'wb')

async def parse_audio(audio_str):
    global f, audio_buffer, i, last_time, times_since_last
    try:
        i += 1
        print(i)
        print(len(audio_str))
        audio = base64.b64decode(audio_str)
        #print(audio)
        #print(audio_str)
        #add to running buffer
        audio_buffer = audio_buffer + audio
        print("Audio after de: {}".format(len(audio)))

        if last_time != -1 and i > 40:
            time_since_last = time.time() - last_time
            times_since_last.append(time_since_last)
            last_time = time.time()
        else:
            last_time = time.time()

        if i == 100:
            print("Average period: {}".format(sum(times_since_last) / len(times_since_last)))
            f.write(audio_buffer)
            f.close()
            #sys.exit()
    except Exception as e:
        print(e)
        pass

async def echo(websocket):
    async for message in websocket:
        #print(message)
        await parse_audio(message)
        #await websocket.send(message)

async def main():
    async with websockets.serve(echo, "0.0.0.0", 8887):
        await asyncio.Future()  # run forever

asyncio.run(main())
