obj =Main_New.o open_directory_new.o
mysql =-I/usr/include/mysql -I/opt/mysql++-3.2.3/include/mysql++ -L/opt/mysql++-3.2.3/lib/ -lmysqlpp

test: $(obj)
	g++ -o test $(obj) `root-config --cflags --glibs` $(mysql)
Main_New.o: Main_New.cpp globle_pars.h 
	g++ -c Main_New.cpp `root-config --cflags --glibs` $(mysql)
open_directory_new.o: open_directory_new.cpp globle_pars.h
	g++ -c open_directory_new.cpp `root-config --cflags --glibs`
clean:
	rm test $(obj)
