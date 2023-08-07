
project = test
objs = main.o test.o ConnectedSearch.o
CXX = g++
CFLAGS = -O3

.SUFFIXES: .o .cpp

$(project): $(objs)
	$(CXX) -o $(project) $(CFLAGS) $^

.cpp .o:
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(project) $(objs)

.PHONY:depend
depend: $(objs:.o= .cpp)
	-@ $(RM) depend.inc
	-@ for i in $^; do\
		cpp -MM $$i | sed "s/\ [_a-zA-Z0-9][_a-zA-Z0-9]*\.cpp//g" >> depend.inc;\
	done

-include depend.inc