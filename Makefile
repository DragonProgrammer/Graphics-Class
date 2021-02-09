CC = g++
CCFLAGS = -g -Wall

rd_view: libcs631.a rd_direct.o pnm_display.o rd_display.o rd_enginebase.o
		$(CC) -o rd_view $(CCFLAGS) libcs631.a rd_direct.o pnm_display.o rd_enginebase.o rd_display.o -lm -lX11

# Add whatever additional files and rules here, and also
# # in the final linking rule above.

#some of these might not need .cpp files

rd_enginebase.o: rd_enginebase.h
#	 	$(CC) $(CCFLAGS) -c rd_enginebase.cpp

rd_display.o: rd_display.h
#	$(CC) $(CCFLAGS) -c rd_display.cc

rd_direct.o: rd_direct.cpp rd_direct.h
	 	$(CC) $(CCFLAGS) -c rd_direct.cpp

pnm_display.o: pnm_display.cpp pnm_display.h
		$(CC) $(CCFLAGS) -c pnm_display.cpp

clean:
	-rm *.o rd_view

