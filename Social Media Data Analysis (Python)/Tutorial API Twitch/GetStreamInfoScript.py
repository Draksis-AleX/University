import json
import numpy
import requests
import datetime
import time
import pandas as pd
from IPython.display import display

#Twitch Client ID
KEY:str = "5p42pziu03o4l4f24ohmxallkf7wy4"

#Twitch api Secret
SECRET:str = "4zll2z343g8e54kfp3vq4u4kfp6xus"

body = {
    'client_id': KEY,
    'client_secret': SECRET,
    "grant_type": 'client_credentials'
}

r = requests.post('https://id.twitch.tv/oauth2/token', body)
keys = r.json()

headers = {
    'Client-ID': KEY,
    'Authorization': 'Bearer ' + keys['access_token']
}

#First pool

new_streams = requests.get('https://api.twitch.tv/helix/streams?type=live&language=it&first=50', headers=headers)
new_streams_info = new_streams.json()

streamdata = {
    "root" : [{
        "date": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),  
        "data": new_streams_info['data']}
    ]
}

with open("stream_data.json", "w") as outfile:
    json.dump(streamdata, outfile)

print("Executed first pool - ["+ datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") +"]")

#---------------------------------------------------------------
count = 0
while count < 23 :
    time.sleep(3600)
    
    new_streams = requests.get('https://api.twitch.tv/helix/streams?type=live&language=it&first=50', headers=headers)
    new_streams_info = new_streams.json()

    new_streamdata = {
        "date": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "data": new_streams_info['data']
    }

    with open('stream_data.json', 'r+', encoding="utf8") as openfile:
        
        streams_info = json.load(openfile)
        streams_info['root'].append(new_streamdata)
        openfile.seek(0)
        json.dump(streams_info,openfile)
        
    print("Executed pool #"+ str(count) +"- ["+ datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") +"]")       
    count = count + 1
        
