import gst, pygst, struct
from simpleOSC import *

(pmin, pmax) = (None, None)
before_p = 0

def listener_on_message (bus, message, data):
  global pmin, pmax, before_p
  s = message.structure
  if s and s.get_name() == "level":
    rms = s['rms']
    p = rms[0]
    if (pmin==None or p<pmin): pmin = p
    if (pmax==None or p>pmax): pmax = p
    if (-30 > before_p and p > -30):
      print "/effect/shout 0 1"
      initOSCClient('127.0.0.1', 9000)
      sendOSCMsg( '/effect/shout', ['0','1'] )
    if (-30 < p):
      print "level:", p
      # print "/effect/shout 0 %s"% (int(p) + 30)
      initOSCClient('127.0.0.1', 9000)
      #sendOSCMsg( '/effect/shout', ['0',str(int(p)+30)] )
      print "/effect/shout 0 0"
      sendOSCMsg( '/effect/shout', ['0','0'] )
    if (-30 < before_p and p < -30):
      print "/effect/shout 0 1"
      initOSCClient('127.0.0.1', 9000)
      sendOSCMsg( '/effect/shout', ['0','1'] )
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
