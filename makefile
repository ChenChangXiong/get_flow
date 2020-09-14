
all:
	#arm-linux-gnueabihf-gcc  main.c read_flow.c  -o  readapp  -pthread
	arm-linux-gcc  main.c read_flow.c  -o  readapp  -pthread
	cp readapp  ~/  -rf
	echo  ===copy finish===
clean:
	rm  readapp
