#HYDRAD Build Configuration
#Will Barnes
#15 December 2015

#Import needed modules
import sys
import os

#Define subdirectories needed for common build
subdirs = ['Radiation_Model','rsp_toolkit','source']

#Build C++ environment
env = Environment(CXX='g++',CXXFLAGS=['-g','-O3','-fno-stack-protector','-Wall'])

#Check OS and change include path
if 'darwin' in sys.platform:
    print("Using Mac OS X compile options.")
    env.Append(CPPPATH=['/opt/local/include','/usr/include/malloc'])
    env.Append(LIBS=['boost_program_options-mt'])
    env.Append(LIBPATH=['/opt/local/lib'])
elif 'linux' in sys.platform:
    print("Using Linux compile options.")
    env.Append(CPPPATH=['/usr/include'])
    env.Append(LIBS=['boost_program_options'])
    env.Append(LIBPATH=['/usr/lib/x86_64-linux-gnu'])
else:
    print("Unrecognized platform. Using Windows compile options.")
    env.Append(CPPPATH=['/usr/local/include'])
    env.Append(LIBS=['boost_program_options'])
    env.Append(LIBPATH=['/usr/local/lib'])
    
#Iterate over subdirectories
allobjs = []
for sd in subdirs:
    consfile = os.path.join(sd,'SConscript')
    allobjs = allobjs + env.SConscript(consfile,exports=['env'])
    
env.Program('bin/IonPopSolver.run',allobjs)