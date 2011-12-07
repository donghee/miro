import gst, pygst, struct
from simpleOSC import *
import pyglet

music = pyglet.media.load('MirLive01.ogg')
player = pyglet.media.Player()
player.queue(music)
player.volumne = 0

(pmin, pmax) = (None, None)
before_p = 0

#ip = "192.168.1.7"
ip = "10.20.40.154"
#ip = "127.0.0.1"
th = 30

def playShoutSound():
  #popen("killall mplayer")
  # cmd = "/usr/bin/mplayer /home/donghee/MirLive01.mp3"
  # os.system(cmd)
  player.volumne=1

def listener_on_message (bus, message, data):
  player.play()
  global pmin, pmax, before_p, th
  s = message.structure
  if s and s.get_name() == "level":
    rms = s['rms']
    p = rms[0]
    if (pmin==None or p<pmin): pmin = p
    if (pmax==None or p>pmax): pmax = p
    if (-th > before_p and p > -th): # reset
      print "/effect/shout 0 0 1"
      initOSCClient(ip, 9000)
      sendOSCMsg( '/effect/shout', ['0','0','1'] )
      player.volumne=0
    if (-th < p): #effecton
      # print "level:", p
      initOSCClient(ip, 9000)
      print "/effect/shout 0 %s 0" % str(int(p)+th)
      sendOSCMsg( '/effect/shout', ['0',str(int(p)+th),'0'] )
      # sound turn on
      playShoutSound()
    if (-th < before_p and p < -th): #effectoff
      print "/effect/shout 0 0 1"
      initOSCClient(ip, 9000)
      sendOSCMsg( '/effect/shout', ['0','0','1'] )
      # sound turn off
      player.volumne=0
    before_p = p
  return True

#listener_desc = 'alsasrc ! level ! fakesink'
listener_desc = 'pulsesrc ! level ! fakesink'
listener = gst.parse_launch(listener_desc)
listener.get_bus().add_watch(listener_on_message, None)

import gobject
mainloop = gobject.MainLoop()
listener.set_state(gst.STATE_PLAYING)

try:
  mainloop.run()
except: # an interruption from Ctrl-C
  print "stopping"

# cleanup
listener.set_state(gst.STATE_NULL)
