#!/usr/bin/python
# -*- coding: utf-8 -*-

#-----------------------------------------------------------------
#-- Python Oscillator client
#-- Juan Gonzalez-Gomez (obijuan).  Feb-2015
#-----------------------------------------------------------------
#-- Controlling the oscillators attached to the servos
#-- The firmware  Oscillator-server-v2 should be upload to the 
#-- zum / arduino board
#--
#--  Interactive version. Use it with ipython / ipython notebook
#--
#--  ipython -i pyosc_i.py
#-----------------------------------------------------------------

import time
import serial
import Oscillator

#-- Change the serial port here
SERIAL_PORT = "/dev/ttyUSB0"

def serial_port(sname = "/dev/ttyUSB0"):
  """Open the serial port"""
  
  try:
    sp = serial.Serial(sname, 19200)
    return sp
  
  except serial.SerialException:
    sys.stderr.write("Error opening the port {0}".format(sname))
    sys.exit(1)

#--- Play a group of oscillators
def play(oscillators):
  for osc in oscillators:
    osc.play()

def stop(oscillators):
  for osc in oscillators:
    osc.stop()
    
def setA(oscillators, A):
  for i,osc in enumerate(oscillators):
    osc.A = A[i]

def setT(oscillators, T = 2000):
  for osc in oscillators:
    osc.T = T
    
def setPh(oscillators, Ph = 0):
  for i, osc in enumerate(oscillators):
    osc.Ph = Ph[i]    
    
def setO(oscillators, O):
  for i,osc in enumerate(oscillators):
    osc.O = O[i]    

#---- Gaits
def home():
  """Put zoby in the home state"""
  setO(all, [a.trim, b.trim, c.trim, d.trim])
  setA(all, [0, 0, 0, 0])
  play(all)

def walk_f():
  setT(all, 1000)
  setPh(all, [0, 0, 90, 90])
  setO(all, [a.trim, b.trim, c.trim, d.trim])
  setA(all, [15, 15, 30, 30])

def walk_b():
  setT(all, 1000)
  setPh(all, [0, 0, -90, -90])
  setO(all, [a.trim, b.trim, c.trim, d.trim])
  setA(all, [15, 15, 30, 30])

def turn_l():
  setT(all, 3000)
  setPh(all, [0, 0, 90, 90])
  setO(all, [a.trim, b.trim, c.trim, d.trim])
  setA(all, [15, 15, 10, 30])
  
def turn_r():
  setT(all, 3000)
  setPh(all, [0, 0, 90, 90])
  setO(all, [a.trim, b.trim, c.trim, d.trim])
  setA(all, [15, 15, 30, 10])

def flap_f():
  setT(all, 1000)
  setPh(all, [0, 180, 90, -90])
  setA(all, [15, 15, 8, 8])
  setO(all, [a.trim - 5, b.trim - 3, c.trim, d.trim])
 
def flap_b():
  setT(all, 1000)
  setPh(all, [0, 180, -90, 90])
  setA(all, [15, 15, 8, 8])
  setO(all, [a.trim - 5, b.trim - 3, c.trim, d.trim])

def moonwalker_r():
  setT(all, 1000)
  setPh(all, [0, 180 + 120, 90, 90])
  setA(all, [25, 25, 0, 0])
  setO(all, [a.trim - 15, b.trim +15, c.trim, d.trim])

def moonwalker_l():
  setT(all, 1000)
  setPh(all, [0, 180 - 120, 90, 90])
  setA(all, [25, 25, 0, 0])
  setO(all, [a.trim - 15, b.trim +15, c.trim, d.trim])

#-------- Interactive version

#-- Open serial port
sp = serial_port(SERIAL_PORT)

#-- Define the oscillators
a = Oscillator.Oscillator(sp, dir = 'a')
b = Oscillator.Oscillator(sp, dir = 'b')
c = Oscillator.Oscillator(sp, dir = 'c')
d = Oscillator.Oscillator(sp, dir = 'd')

#-- All the oscillators
all = [a, b, c, d]

print("Waiting for the zum to boot up")
time.sleep(3)
print("ready")


#--- Servos TRIM: this is the offset that should be applied so that the
#--  servos are mecanically at home. If the robot were perfectly mounted
#--  this value is 0
a.trim = -18
b.trim = 7
c.trim = -6
d.trim = -11

#-- Initial state: stoped
home()
time.sleep(2)

#-- Gait 1: forward


"""

//-- Gait: Superposition: moonwalker + fordward
//const int A[4]= {25, 25, 30, 30};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Swing
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

//-- Gait: up-down
//const int A[4]= {25, 25, 0, 0};
//const int O[4] = {-18 - 15, 7 + 15, -6, -11};
//const int T =1000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)};




//-- Gait: Moving forward faster - small steps
//const int A[4]= {10, 10, 10, 10};
//const int O[4] = {-18, 7, -6, -11};
//const int T =500;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 

//-- Gait: Moving backwards very slow
//const int A[4]= {15, 15, 30, 30};
//const int O[4] = {-18, 7, -6, -11};
//const int T =3000;
//const double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 


"""

