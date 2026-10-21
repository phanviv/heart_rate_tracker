CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp tasks_data.cpp tasks_analysis.cpp reading.cpp readinglog.cpp \
       user.cpp sensor.cpp alert.cpp filemanager.cpp

tracker: $(SRCS) *.h
	$(CXX) $(CXXFLAGS) $(SRCS) -o tracker

run: tracker
	./tracker

clean:
	rm -f tracker
