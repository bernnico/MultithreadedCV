# To build set current opencv version (opencv_worldXXX, opencv_worldXXXd)
# and edit the paths to the .lib files and include directory

# To run add c:/lib/opencv/build/install/x86/vc16/bin to the env PATH



INCLUDEPATH += c:/lib/opencv/build/install/include
Debug: { 
LIBS += -lc:/lib/opencv/build/install/x86/vc16/lib/opencv_world480d
} 
Release: { 
LIBS += -lc:/lib/opencv/build/install/x86/vc16/lib/opencv_world480
}