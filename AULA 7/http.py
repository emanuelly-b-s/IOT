# -*- coding: utf-8 -*-
"""
Created on Tue Mar  7 08:36:38 2023

@author: Emanuelly S
"""

import requests 
import json 
import pyodbc
import time
import matplotlib.pyplot as plt
import pyodbc
import numpy as np
import pandas as pd
import seaborn as sns



proxies = {'https':"https://disrct:etsds10243110@10.224.200.26:8080"}
r = requests.get('https://chat.openai.com/chat', proxies=proxies)


#Pegar dados Firebase -------------------------------------------------------------------------------------------
def Sinal():
    url_temperatura = 'https://teste-esp-temp-default-rtdb.firebaseio.com/<Emanuelly>/Sensor/temperatura.json'
    url_umidade = 'https://teste-esp-temp-default-rtdb.firebaseio.com/<Emanuelly>/Sensor/umidade.json'
    
    temperatura = float(requests.get(url_temperatura, proxies=proxies).content)
    umidade = float(requests.get(url_umidade, proxies=proxies).content)
    
    return temperatura, umidade


#Inserir dados -------------------------------------------------------------------------------------------
def InserirBD(sinal):
    server = 'CT-C-0013M\SQLEXPRESS'
    database = 'tempdb'
    cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
    global cursor
    cursor = cnxn.cursor()
    cursor.execute(f"INSERT dbo.Sensor (temp, umidade) VALUES ({sinal[0]},{sinal[1]});") 
    cursor.commit()
    print("Inserido com sucesso!")
    
    
#Print py-------------------------------------------------------------------------------------------
def Apresentar(sinal):
    print(f"Temp: {sinal[0]}")
    print(f"Temp: {sinal[1]}")

    
#Chama fun inserir bd a cada 2 min -------------------------------------------------------------------------------------------
while True:
    valores = Sinal()   
    Apresentar(valores)
    InserirBD(Sinal())
    
    cursor.execute('SELECT temp, umidade, timestamp FROM dbo.Sensor')
    row = cursor.fetchone()
    temperatura = []
    umidade = []
    timestamp = []

    while row:
        temperatura.append(row[0])
        umidade.append(row[1])
        timestamp.append(str(row[2]))
        row = cursor.fetchone()
            
    df = pd.DataFrame({"Temperatura":temperatura, "Tempo":timestamp, "Umidade":umidade})
    
    df['Tempo'] = pd.to_datetime(df["Tempo"])
    tempo = list(df['Tempo'])
    hora_minuto = []
    for i in tempo:
        i = i.strftime('%H:%M')
        hora_minuto.append(i)
        
    hora_minuto = pd.to_datetime(hora_minuto)
    df['sla'] = hora_minuto
    
    sns.relplot(x= "sla", y="Temperatura", data=df, kind="line")
    plt.title("Temperatura por Tempo")
    plt.xticks(rotation=90)
    plt.show()
    time.sleep(120)
    

# Criar dtF-------------------------------------------------------------------------------------------


# -------------------------------------------------------------------------------------------


#  url = 'https://random.dog/woof.json'
# img_data = requests.get(url,proxies=proxies).content
# new_url = json.loads(img_data)['url']
# img = requests.get(new_url,proxies=proxies).content
# with open('dog.jpg','wb') as dog_file:
#     dog_file.write(img)


# -------------------------------------------------------------------------------------------

# Faça um programa utilizando a API https://agify.io/, faça um GET request enviando como
# parâmetro o nome de uma pessoa, o dado retornado deve ser a previsão de idade para a
# pessoa de acordo com seu nome.

# name = input("Digite o nome da pessoa: ")

# url = f"https://api.agify.io?name={name}&country_id=BR"
# response = requests.get(url,proxies=proxies)
# if response.status_code == 200:
#     data = response.json()
#     print(f"A idade prevista para {name} é {data['age']} anos.")
# else:
#     print(f"Erro ao realizar a requisição: {response.status_code}")
    
# -------------------------------------------------------------------------------------------

    
    