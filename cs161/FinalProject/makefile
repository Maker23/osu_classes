
program_NAME := myprogram
program_CXX_SRCS := $(wildcard *.cpp)
program_OBJS := ${program_CXX_SRCS:.cpp=.o}

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
