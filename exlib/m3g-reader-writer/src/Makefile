SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
HEADERS  = $(wildcard *.hpp)
CXX      = g++ 
CXXFLAGS = -Wall -g -fno-strict-aliasing -fPIC
INSTALL_DIR = NOTDEFINED

LD       = ar
LDFLAGS  = -srv 
LIBS     = -lz
TARGET   = libM3GReaderWriter.a


all: $(OBJS)
	$(LD) $(LDFLAGS) $(LIB) $(TARGET) $^
	@echo done.

install: $(TARGET)
	cp $(TARGET) $(INSTALL_DIR)
	cp $(HEADERS) $(INSTALL_DIR)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c


depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ *.bak
	@echo done.

# DO NOT DELETE

M3GReader.o: M3GReader.hpp M3GStruct.hpp
M3GStruct.o: M3GStruct.hpp
M3GWriter.o: M3GWriter.hpp M3GStruct.hpp
