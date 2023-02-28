all:
	gcc -g3 -o obj/main.o test/main.c src/list.c src/hm.c src/mythread.c -I include/
	./obj/main.o data/in1.txt data/in2.txt data/in3.txt data/in4.txt

list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test  -I include/
hashmap:
	gcc -o obj/hm_test test/hashmap_test.c src/hm.c src/list.c src/mythread.c
	./obj/hm_test  -I include/

doc:
	doxygen Doxyfile
clean:
	rm -f obj/*
	rm -fr doc/*


.PHONY: all test clean
