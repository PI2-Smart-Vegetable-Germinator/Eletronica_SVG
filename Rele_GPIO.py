import RPi.GPIO as GPIO
 
GPIO.setmode(GPIO.BOARD)
 
GPIO.setup(12, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)

while (True)
if (luximeter <= 10000)
    GPIO.output(12,1)
    
else:
    GPIO.output(12,0)

if (SRUS >= 3000)
    GPIO.output(12,1)
    
else:
    GPIO.output(12,0)
