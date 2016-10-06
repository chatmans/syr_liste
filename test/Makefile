# root of Google Test
GTEST_DIR = /home/pumicerd/GoogleTest
INCDIR    = ../include

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include -I$(INCDIR)

# Flags passed to the C compiler.
CFLAGS += -g -Wall

# Flags passed to the C++ compiler.
CXXFLAGS += $(CFLAGS)

# libs to link statically
LIBS  =  $(GTEST_DIR)/lib/libgtest.a $(GTEST_DIR)/lib/libgtest_main.a

%.o : %.cc %.hh
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

%.o : %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

all : test_unitaire_list test

test_unitaire_list : test_unitaire_list.o ../obj/list.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

../obj/list.o : ../src/list.c ../include/list.h
	$(CC) -c -I$(INCDIR) $(CFLAGS) ../src/list.c -o ../obj/list.o

test : test_unitaire_list
	./test_unitaire_list

raz clean :
	-rm *.o *~ test_unitaire_list
