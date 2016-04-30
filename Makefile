CXX=g++
CXXFLAGS=-Wall -g -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LDFLAGS=-lncurses
SRCS=src/main.cpp src/CCell.cpp src/CHelpController.cpp src/CTable.cpp src/CText.cpp src/CAbstractController.cpp src/CEquation.cpp src/CRuntime.cpp src/CTableController.cpp src/CSplashscreenController.cpp  src/CWelcomeController.cpp  src/CExpressionParser.cpp

OBJS=$(subst .cpp,.o,$(SRCS))
EXEC=spreadsheet

all: doc compile

compile: $(OBJS)
	$(CXX)  $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

main.o: src/main.cpp CRuntime.h
CAbstractController.o: src/CAbstractController.cpp src/CAbstractController.h
CSplashscreenController.o: src/CSplashscreenController.cpp src/CSplashscreenController.h src/CAbstractController.h
CWelcomeController.o: src/CWelcomeController.cpp src/CWelcomeController.h src/CAbstractController.h
CHelpController.o: src/CHelpController.cpp src/CHelpController.h src/CAbstractController.h
CTableController.o: src/CTableController.cpp src/CTableController.h src/CAbstractController.h src/CTable.h src/CRuntime.h
CRuntime.o: src/CRuntime.h, src/CRuntime.cpp src/CAbstractController.h src/CSplashscreenController.h src/CWelcomeController.h src/CHelpController.h src/CTableController.h
CTable.o: src/CTable.cpp src/CTable.h src/CCell.h src/CText.h src/CEquation.h
CCell.o: src/CCell.cpp src/CCell.h
CText.o: src/CText.cpp src/CText.h src/CCell.h
CEquation.o: src/CEquation.cpp src/CEquation.h src/CCell.h src/CTable.h src/CExpressionParser.h
CExpressionParser.o: src/CExpressionParser.cpp src/CExpressionParser.h

clean:
	rm -rf sec/*.o spreadsheet doc

run:
	./spreadsheet

doc: $(OBJS)
	cd ./src/;\
	doxygen ../Doxyfile
