#!/usr/bin/python
import paho.mqtt.client as mqtt


def on_connect(client, obj, flags, rc):
     pass

def on_message(client, obj, msg):
 # print(msg.topic+" "+str(msg.qos)+" "+str(msg.payload))
     topic = msg.topic.split("/")
     if topic[0]=="authenticate":
         modules.append({'deviceCode': topic[1], 'key': msg.payload})

def on_publish(client, obj, mid):
 # print("mid: "+str(mid))
     pass

def on_subscribe(client, obj, mid, granted_qos):
     pass

def on_log(client, obj, level, string):
     pass

client = mqtt.Client()
client.on_message = on_message
client.on_connect = on_connect
client.on_publish = on_publish
client.on_subscribe = on_subscribe

client.connect("localhost", 1883, 60)
client.loop_start()
