# Build script for the Ion_Pop_Solver code
# Edit the command below to include optimisation flags for the compiler

g++ -O3 Radiation_Model/source/ionfrac.cpp Radiation_Model/source/element.cpp Radiation_Model/source/radiation.cpp source/file.cpp source/fitpoly.cpp source/main.cpp -o Ion_Pop_Solver.exe