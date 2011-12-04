# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

OF_ROOT = .


# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS =  -I src/ \
    -I addons/ofxTuioWrapper/core \
    -I addons/ofxTuioWrapper/ \
    -I addons/ofxOsc/libs/oscpack/include \
    -I addons/ofxOsc/libs/oscpack/include/osc \
    -I addons/ofxOsc/libs/oscpack/include/ip \
    -I addons/ofxOsc/src \
    -I addons/ofxMSAInteractiveObject/src \
    -I addons/ofxhGui/src \
    -I addons/ofxhUtils/src/hEvents \
    -I addons/ofxhUtils/src/hStringUtils \
    -I addons/ofxhUtils/src/hTable



# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

USER_LDFLAGS = addons/ofxOsc/libs/oscpack/lib/linux64/liboscpack.a


# use this to add system libraries for example:
# USER_LIBS = -lpango
 
USER_LIBS =


# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -Os


EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj"
