import pyb
timer3 = pyb.Timer(3, freq=1000000)
p5 = pyb.Pin("B5", pyb.Pin.OUT)
ch2 = timer3.channel(2, pyb.Timer.PWM, pin=p5, pulse_width_percent=50)
