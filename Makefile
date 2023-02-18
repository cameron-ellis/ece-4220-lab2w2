Lab2_Week2 : Lab2-Week2-Approach2.c
		gcc $^ -o $@ -lpthread -lrt


.PHONY : run
run :
		sudo ./Lab2_Week2

.PHONY : clean
clean :
		rm -rf *.o *~ Lab2_Week2
		clear