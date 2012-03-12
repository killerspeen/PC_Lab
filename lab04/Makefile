
all: rmfifo fifo
	gcc -o reader reader.c alarm/alarm.c
	gcc -o writer writer.c alarm/alarm.c

fifo:
	mkfifo data
	mkfifo ack

rmfifo:
	rm data ack

clean: rmfifo
	rm reader writer
