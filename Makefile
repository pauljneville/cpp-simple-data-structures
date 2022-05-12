CC=g++

CXXFLAGS=-Wall -pedantic -std=c++14

SRCS = utility.cpp linkedlist.cpp tree.cpp stdlist.cpp stdmultiset.cpp stdvector.cpp bpooptions.cpp
OBJS = $(SRCS:.cpp=.o)

all: ass1

$(OBJS): %.o : %.h

main.o: utility.h linkedlist.h tree.h stdlist.h stdmultiset.h stdvector.h bpooptions.h

.cpp.o:
	$(CC) $(CXXFLAGS) -c $<

ass1: $(OBJS)
	$(CC) $(CXXFLAGS) -lboost_program_options $^ main.cpp -o $@

# main.o: main.cpp
#	$(CC) $(CXXFLAGS) -c main.cpp

#linkedlist.o: linkedlist.cpp linkedlist.h
#	$(CC) $(CXXFLAGS) -c linkedlist.cpp

#tree.o: tree.cpp tree.h
#	$(CC) $(CXXFLAGS) -c tree.cpp
		
clean:
	rm -f $(OBJS) ass1
#source /opt/rh/devtoolset-6/enable

# undefined reference to `vtable for <class name>' if not defined here