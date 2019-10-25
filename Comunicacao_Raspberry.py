#!/usr/bin/env python 3
import serial
comunicacaoSerial = serial.Serial('/dev/ttyACMo', 9600) #substituindo ttyACM0 pelo USB da ESP32 
                                                        

while True: 
	print (comunicacao.Serial.readLine()) #imprime no terminal da raspberry
