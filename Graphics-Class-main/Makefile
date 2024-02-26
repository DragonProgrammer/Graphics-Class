#CXX = clang++
CXX = g++
#CCFLAGS = -g -Wall -fsanitize=memory -fPIE -fno-omit-frame-pointer
CCFLAGS = -g -Wall  
#CXXFLAGS = -g -Wall -fsanitize=address -fno-omit-frame-pointer

rd_view: libcs631.a rd_direct.o pnm_display.o global.o frame.o color.o  
		$(CXX) -o rd_view $(CXXFLAGS) libcs631.a rd_direct.o color.o pnm_display.o  frame.o globals.o  -lm -lX11

# Add whatever additional files and rules here, and also
# # in the final linking rule above.

#some of these might not need .cpp files

color.o: color.cpp color.h	
		$(CXX) $(CXXFLAGS) -c color.cpp

# for some reason this is not accptable for the maker file wile rd_display.o or rd_enginebase.0o works
# puting er_error in one of the other lines does work
#rd_error.o: rd_error.h 
	#	$(CXX) $(CXXFLAGS) -c rd_error.cpp

global.o: globals.cpp globals.h
		$(CXX) $(CXXFLAGS) -c globals.cpp

frame.o: frame.h frame.cpp
		$(CXX) $(CXXFLAGS) -c frame.cpp

#rd_enginebase.o: rd_enginebase.h
#	 	$(CC) $(CCFLAGS) -c rd_enginebase.cpp

#rd_display.o: rd_display.h
#	$(CC) $(CCFLAGS) -c rd_display.cc

rd_direct.o: rd_direct.cpp rd_direct.h 
	 	$(CXX) $(CXXFLAGS) -c rd_direct.cpp

pnm_display.o: pnm_display.cpp pnm_display.h
		$(CXX) $(CXXFLAGS) -c pnm_display.cpp

clean:
	-rm *.o rd_view

