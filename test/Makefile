objs = zip_test.o enumerate_test.o test_main.o
program = itertools_test
CXXFLAGS = -std=c++1y
LDFLAGS = -lboost_unit_test_framework

all : ${program}

${program} : ${objs}
	${CXX} ${LDFLAGS} $^ -o $@

test_main.o: test_main.cpp
	${CXX} ${CXXFLAGS} -c $<

zip_test.o: zip_test.cpp ../include/zip.hpp 
	${CXX} ${CXXFLAGS} -c $<

enumerate_test.o: enumerate_test.cpp ../include/enumerate.hpp 
	${CXX} ${CXXFLAGS} -c $<

.PHONY: clean
clean:
	${RM} ${program}
	${RM} ${objs}

.PHONY: test
test: ${program}
	./${program}
