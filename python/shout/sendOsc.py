>>> from simpleOSC import *
>>> initOSCClient('127.0.0.1', 9000)
>>> sendOSCMsg('/scene', ['0','0'])
>>> sendOSCMsg('/effect/shout', ['0','0'])
