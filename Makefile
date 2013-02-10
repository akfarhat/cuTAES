CFILES = main.cpp ApplicationWindow.cpp ApplicationWindow.h Student.h Student.cpp Application.h Application.cpp Makefile courses.txt readme.txt
CFLAGS = -g -c
PACKAGE = `pkg-config gtkmm-3.0 --cflags --libs`

cutaes: main.o ApplicationWindow.o Student.o Application.o
	g++ -o cutaes main.o ApplicationWindow.o Student.o Application.o $(PACKAGE) 

main.o: main.cpp ApplicationWindow.h
	g++ $(CFLAGS) main.cpp $(PACKAGE)

ApplicationWindow.o: ApplicationWindow.cpp ApplicationWindow.h Student.h Application.h
	g++ $(CFLAGS) ApplicationWindow.cpp $(PACKAGE)

Student.o: Student.cpp Student.h
	g++ $(CFLAGS) Student.cpp

Application.o: Application.cpp Application.h Student.h
	g++ $(CFLAGS) Application.cpp

clean: 
	rm -f *.o cutaes

tar:
	tar -cvsf cutaes.tar $(CFILES)
