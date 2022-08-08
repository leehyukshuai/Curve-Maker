objects = curve.o fraction.o main.o 

curve : $(objects)
	g++ -o curve $(objects)

curve.o : curve.cpp curve.h
	g++ -c curve.cpp

fraction.o : fraction.cpp fraction.h
	g++ -c fraction.cpp

main.o : main.cpp curve.o
	g++ -c main.cpp

clear :
	del *.o