
# Added "-static" option to solve the following running error:
# "<binary_file_name>: /usr/lib/libstdc++.so.6: version `GLIBCXX_3.4.14' not found 
# (required by <binary_file_name>)"
# 
#CPPFLAGS = -g -Wall -std=c++0x -static
# This option will make the executable file's size much larger

OBJ=test.o brute.o larger_equal_nlogn.o less_equal_n.o epi_less_equal_nlogn.o larger_equal_n.o

test: ${OBJ}
	g++ -o test ${OBJ}

clean:
	rm -f main *.o *~
