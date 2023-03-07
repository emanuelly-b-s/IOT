# -*- coding: utf-8 -*-
"""
Created on Tue Mar  7 08:36:38 2023

@author: Emanuelly S
"""

import requests 
import json 

proxies = {'https':"https://disrct:etsds10243110@10.224.200.26:8080"}
r = requests.get('https://chat.openai.com/chat', proxies=proxies)

# url = 'https://random.dog/woof.json'
# img_data = requests.get(url,proxies=proxies).content
# new_url = json.loads(img_data)['url']
# img = requests.get(new_url,proxies=proxies).content
# with open('dog.jpg','wb') as dog_file:
#     dog_file.write(img)

url_temperatura = 'https://teste-esp-temp-default-rtdb.firebaseio.com/<Emanuelly>/Sensor/temperatura.json'
url_umidade = 'https://teste-esp-temp-default-rtdb.firebaseio.com/<Emanuelly>/Sensor/umidade.json'

temperatura = float(requests.get(url_temperatura, proxies=proxies).content)
umidade = float(requests.get(url_umidade, proxies=proxies).content)


print(temperatura, umidade)
