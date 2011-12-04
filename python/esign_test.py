import socket
from array import *
from crc import *
import random
import time

def c(r,g,b):
  return (r,g,b)

class Esign():
  def __init__(self, host, _port_count, _cluster_count, _data_size):
    self.host = host
    self._port = 8001
    self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    self.ports_data = [0 for i in range(_port_count*_cluster_count*3)]
    self.p = 0

    self.port_count = _port_count
    self.cluster_count = _cluster_count
    self.data_size = _data_size

  def random_color(self):
    self.ports_data = [int(random.randint(0,100)) for i in range(self.port_count*self.cluster_count*3)]

  def clear(self):
    self.background(0)
    self.show()

  def dimming(self,up):
    self.ports_data = [self.p for i in range(self.port_count*self.cluster_count*3)]
    self.p=self.p+(1*up)
    if self.p == 255:
      self.p=0
    if self.p<0:
      self.p=255

  def background(self, grey):
    self.ports_data = [grey for i in range(self.port_count*self.cluster_count*3)]

  def set_colors(self, color):
	for i in range(self.port_count):
		for j in range(self.cluster_count):
			self.set_color(i,j,color)

  def set_color(self, port, y, color):
    rgb_clusters = self.cluster_count*3
    color_index = port * rgb_clusters + (y*3)
    self.ports_data[color_index] = color[0]
    self.ports_data[color_index+1] = color[1]
    self.ports_data[color_index+2] = color[2]
  
  def build_2packets(self,size):
    return [(size&0xff), ((size&0xff00)>>8)] 

  def get_start_position(self,sent_data_size):
    return self.build_2packets(sent_data_size)

  def get_data_size(self,data_size):
    return self.build_2packets(data_size)

  def get_port_length(self,port_length):
    return self.build_2packets(port_length)

  def get_cluster_count(self,cluster_count):
    return self.build_2packets(cluster_count)

  def packet(self,port_count, cluster_count, packet_count, packet_index, sent_datas, data_size):
    p_frame_syn = [0x16,0x16,0x16,0x16]
    p_id = [0x00,0x00]
    p_command = [0x30]
    p_length = self.build_2packets(data_size+28)
    p_data_frame_index = [0x00,0x00]
    p_image_mode = [0x01]
    p_ports = [port_count]
    _cluster_count = self.get_cluster_count(cluster_count)
    p_port1 = _cluster_count
    p_port2 = _cluster_count
    p_port3 = _cluster_count
    p_port4 = _cluster_count
    p_port5 = _cluster_count
    p_port6 = _cluster_count
    p_port7 = _cluster_count
    p_port8 = _cluster_count
    p_image_time = [0x00,0x00]
    p_packet_id = [(packet_count<<4)+packet_index]
    p_reserved = [0x00]
    p_start_position = [0x00,0x00]
    p_start_position = self.get_start_position(sent_datas)
    p_data_size = self.get_data_size(data_size)
    _port_data = self.ports_data[sent_datas:sent_datas+data_size]
    packet = p_id + p_command + p_length+ p_data_frame_index + p_image_mode + p_ports + p_port1 + p_port2 + p_port3 + p_port4 + p_port5 + p_port6 + p_port7+ p_port8 + p_image_time +p_packet_id + p_reserved+ p_start_position + p_data_size  + _port_data
    _crc = build_crc_ccitt(packet)
    p_crc = [ _crc >> 8, _crc & 0xff]
    p_etx = [0xf5]
    packet = p_frame_syn + packet + p_crc  + p_etx
    p = array('B', packet)
    self.s.sendto(p,(self.host,self._port))

  def show(self):
    port_count=self.port_count
    cluster_count=self.cluster_count
    data_size=self.data_size

    all_packet_size = 3*port_count*cluster_count
    packet_count = (all_packet_size / data_size) + 1
    remain_data = all_packet_size % data_size

    for i in range(packet_count):
      if i == packet_count-1:
        self.packet(port_count,cluster_count,packet_count, packet_index=i+1, sent_datas=data_size*i, data_size=remain_data)
        break
      self.packet(port_count,cluster_count,packet_count, packet_index=i+1, sent_datas=data_size*i, data_size=data_size)

def led(e, on):
  if on:
    e.background(255)
  else:
    e.background(0)
  e.show()

def led_port(e, port, cluster_count, on):
  e.background(0)
  e.show()
  if on:
    color = c(255,255,255)
  else:
    color = c(0,0,0)
  for i in range(cluster_count):
    e.set_color(port,i,color)
  e.show()


def led_all_flash(e):
  for i in range(8):
    e.background(255)
    e.show()
    time.sleep(0.8) # 30 fps
    e.background(0)
    e.show()
    time.sleep(0.8) # 30 fps

def led_swipe(e, port, cluster_count, color,delay):
  e.background(0)
  for i in range(cluster_count):
    e.set_color(port,i,c(255,0,255))
    e.show()
    time.sleep(delay)
  for i in range(cluster_count-1,-1,-1):
    e.set_color(port,i,c(0,0,0))
    e.show()
    time.sleep(delay)

def two_led_swipe(e, port, cluster_count, color,delay):
  e.background(0)
  for i in range(0,cluster_count,2):
    e.set_color(port,i,c(255,0,255))
    e.set_color(port,i+1,c(255,0,255))
    e.show()
    time.sleep(delay)
  # cluster_count = (cluster_count % 2 == 0) ? cluster_count -1
  # if cluster_count is even, cluster_count-1,-1,-2
  # if cluster_count is odd, cluster_count -1, -2
  for i in range(cluster_count-1,-1,-2):
    e.set_color(port,i,c(0,0,0))
    e.set_color(port,i-1,c(0,0,0))
    e.show()
    time.sleep(delay)

def dimming_test(e):
  e.background(0)
  e.show()
  for i in range(255):
    e.background(i)
    e.show()
    time.sleep(0.005)
  for i in range(255,-1,-1):
    e.background(i)
    e.show()
    time.sleep(0.005)

data_size = 1432
e1 = Esign('192.168.1.11', _port_count=8, _cluster_count=175, _data_size=data_size)
e2 = Esign('192.168.1.12', _port_count=8, _cluster_count=175, _data_size=data_size)
e3 = Esign('192.168.1.13', _port_count=8, _cluster_count=175, _data_size=data_size)
e4 = Esign('192.168.1.14', _port_count=8, _cluster_count=175, _data_size=data_size)
e5 = Esign('192.168.1.15', _port_count=8, _cluster_count=175, _data_size=data_size)
e6 = Esign('192.168.1.16', _port_count=8, _cluster_count=175, _data_size=data_size)
e7 = Esign('192.168.1.17', _port_count=8, _cluster_count=175, _data_size=data_size)
e8 = Esign('192.168.1.18', _port_count=8, _cluster_count=175, _data_size=data_size)
e9 = Esign('192.168.1.19', _port_count=8, _cluster_count=175, _data_size=data_size)

esigns = [e1,e2,e3,e4,e5,e6,e7,e8,e9]

<<<<<<< HEAD
delay = 0.1
length = 175
=======
##for i in range(500):
##  for e in esigns:
##    led(e,True)
##  time.sleep(0.01)
##  for e in esigns:
##    led(e,False)
##  time.sleep(0.01)
  
e=e2
delay = 0.1
length = 175
p=5
#two_led_swipe(e,0,length, c(255,0,255),delay)
#two_led_swipe(e,1,length, c(255,0,255),delay)
#two_led_swipe(e,p,length, c(255,0,255),delay)

#two_led_swip(e,3, length, c(255,0,255),delay)

#two_led_swipe(e,4, length, c(255,0,255),delay)
#two_led_swipe(e,5, length, c(255,0,255),delay)
#two_led_swipe(e,6, length, c(255,0,255),delay) 
#two_led_swipe(e,7, length, c(255,0,255),delay)

#led(e,True)
#led(e,False)

#led_port(e, p, length, True)
#led_port(e, p, length, False)

#led_all_flash(e)
#led_all_flash(e)
#led_all_flash(e)
#led_all_flash(e)
#led_all_flash(e)

#dimming_test(e)
>>>>>>> 10634666ff6aacb7de28181d98361feacb583f99

from Tkinter import *

master = Tk()

def port_on_cb():
    e=int(controller_entry.get())
    esign = esigns[e-1]
    p=int(port_entry.get())
    led_port(esign, p-1, length, True)
    print "PORT ON"

def port_off_cb():
    e=int(controller_entry.get())
    esign = esigns[e-1]
    p=int(port_entry.get())
    led_port(esign, p-1, length, False)
    print "PORT OFF"

def port_blink_cb():
    e=int(controller_entry.get())
    esign = esigns[e-1]
    p=int(port_entry.get())
    for i in range(5):
        led_port(esign, p-1, length, True)
        time.sleep(0.2)
        led_port(esign, p-1, length, False)
        time.sleep(0.2)
    print "PORT BLINK"

def port_flow_cb():
    delay = 0.1
    e=int(controller_entry.get())
    esign = esigns[e-1]
    p=int(port_entry.get())
    two_led_swipe(esign,p-1,length, c(255,0,255),delay)
    print "FLOW!"

<<<<<<< HEAD
=======
def port_orange_cb():
	for esign in esigns:
		esign.clear()
		esign.set_colors(c(245,202,84))
		esign.show()
	print "ORANGE!"

>>>>>>> 10634666ff6aacb7de28181d98361feacb583f99
def port_white_cb():
	white=w.get()
	for esign in esigns:
		esign.clear()
		esign.set_colors(c(white,white,white))
		esign.show()
	print "WHITE!"

<<<<<<< HEAD
=======
def port_yellow_cb():
	for esign in esigns:
		esign.clear()
		esign.set_colors(c(250,231,182))
		esign.show()
	print "YELLOW!"

>>>>>>> 10634666ff6aacb7de28181d98361feacb583f99
def port_rgb_cb():
	_r = r.get()
	_g = g.get()
	_b = b.get()
	for esign in esigns:
		esign.clear()
		esign.set_colors(c(_r,_g,_b))
		esign.show()
	print "RGB"
	print _r,_g,_b

def esigns_clear_cb():
	for esign in esigns:
		esign.clear()

Label (text="Controller (1-9)").pack(side=TOP,padx=10,pady=2)
controller_entry = Entry(master, text="1")
controller_entry.pack(side= TOP, padx=10, pady=2)

Label (text="Port (1-8)").pack(side=TOP, padx=10, pady=2)
port_entry = Entry(master)
port_entry.pack(side= TOP,padx=10,pady=5)

port_on = Button(master,  text="ON", command=port_on_cb)
port_on.pack(side=LEFT)
port_off = Button(master, text="OFF", command=port_off_cb)
port_off.pack(side=LEFT)
port_blink = Button(master, text="BLINK", command=port_blink_cb)
port_blink.pack(side=RIGHT)
port_flow = Button(master, text="FLOW", command=port_flow_cb)
port_flow.pack(side=RIGHT,pady=10)

w = Scale(master, from_=0, to=255, orient=HORIZONTAL)
w.pack()
white_button = Button(master, text="WHITE", command=port_white_cb)
white_button.pack()
<<<<<<< HEAD
=======
orange_button = Button(master, text="ORANGE", command=port_orange_cb)
orange_button.pack()
yellow_button = Button(master, text="YELLOW", command=port_yellow_cb)
yellow_button.pack()
>>>>>>> 10634666ff6aacb7de28181d98361feacb583f99
turnoff_button = Button(master, text="ALL OFF", command=esigns_clear_cb)
turnoff_button.pack()

r = Scale(master, from_=0, to=255, orient=HORIZONTAL)
r.pack()

g = Scale(master, from_=0, to=255, orient=HORIZONTAL)
g.pack()

b = Scale(master, from_=0, to=255, orient=HORIZONTAL)
b.pack()

rgb_button = Button(master, text="RGB", command=port_rgb_cb)
rgb_button.pack()

mainloop()

# orange
# 245,202,84
# 255-> 200
# 250,231,182
