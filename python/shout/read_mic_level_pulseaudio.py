import gst, pygst, struct
from simpleOSC import *

(pmin, pmax) = (None, None)
before_p = 0

#ip = "192.168.1.7"
ip = "127.0.0.1"

def listener_on_message (bus, message, data):
  global pmin, pmax, before_p
  s = message.structure
  if s and s.get_name() == "level":
    rms = s['rms']
    p = rms[0]
    if (pmin==None or p<pmin): pmin = p
    if (pmax==None or p>pmax): pmax = p
    if (-10 > before_p and p > -10): # reset
      print "/effect/shout 1 0 1"
      initOSCClient(ip, 9000)
      sendOSCMsg( '/effect/shout', ['1','0','1'] )
    if (-10 < p): #effecton
      print "level:", p
      initOSCClient(ip, 9000)
      print "/effect/shout 1 %s 0" % str(int(p)+30)
      sendOSCMsg( '/effect/shout', ['1',str(int(p)+30),'0'] )
    if (-10 < before_p and p < -10): #effectoff
      print "/effect/shout 1 0 1"
      initOSCClient(ip, 9000)
      sendOSCMsg( '/effect/shout', ['1','0','1'] )
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
