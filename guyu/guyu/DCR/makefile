
obj =Main_New.o open_directory_new.o

test: $(obj)
	g++ -o test $(obj) `root-config --cflags --glibs` 
Main_New.o: Main_New.cpp globle_pars.h 
	g++ -c Main_New.cpp `root-config --cflags --glibs`
open_directory_new.o: open_directory_new.cpp globle_pars.h
	g++ -c open_directory_new.cpp `root-config --cflags --glibs`
clean:
	rm test $(obj)
