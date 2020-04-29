all:
	gcc FIFO.c Scheduler.c -o FIFO
	gcc RR.c Scheduler.c -o RR
	gcc SJF.c Scheduler.c -o SJF
	gcc PSJF.c Scheduler.c -o PSJF
	gcc main.c -o main
demo:
	sudo dmesg -C
	sudo ./main < Input/TIME_MEASUREMENT.txt
	dmesg | grep Project
	sudo dmesg -C
	sudo ./main < Input/FIFO_1.txt 
	dmesg | grep Project
	sudo dmesg -C
	sudo ./main < Input/RR_2.txt 
	dmesg | grep Project 
	sudo dmesg -C
	sudo ./main < Input/SJF_3.txt  
	dmesg | grep Project 
	sudo dmesg -C
	sudo ./main < Input/PSJF_4.txt  
	dmesg | grep Project
	sudo dmesg -C	
Time:
	sudo dmesg -C
	sudo ./main < Input/TIME_MEASUREMENT.txt > Output/TIME_MEASUREMENT_stdout.txt
	dmesg | grep Project > Output/TIME_MEASUREMENT_dmesg.txt
	sudo dmesg -C
FIFO:
	sudo dmesg -C
	sudo ./main < Input/FIFO_1.txt > Output/FIFO_1_stdout.txt
	dmesg | grep Project > Output/FIFO_1_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/FIFO_2.txt > Output/FIFO_2_stdout.txt
	dmesg | grep Project > Output/FIFO_2_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/FIFO_3.txt > Output/FIFO_3_stdout.txt
	dmesg | grep Project > Output/FIFO_3_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/FIFO_4.txt > Output/FIFO_4_stdout.txt
	dmesg | grep Project > Output/FIFO_4_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/FIFO_5.txt > Output/FIFO_5_stdout.txt
	dmesg | grep Project > Output/FIFO_5_dmesg.txt
	sudo dmesg -C
RR:
	sudo dmesg -C
	sudo ./main < Input/RR_1.txt > Output/RR_1_stdout.txt
	dmesg | grep Project > Output/RR_1_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/RR_2.txt > Output/RR_2_stdout.txt
	dmesg | grep Project > Output/RR_2_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/RR_3.txt > Output/RR_3_stdout.txt
	dmesg | grep Project > Output/RR_3_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/RR_4.txt > Output/RR_4_stdout.txt
	dmesg | grep Project > Output/RR_4_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/RR_5.txt > Output/RR_5_stdout.txt
	dmesg | grep Project > Output/RR_5_dmesg.txt
	sudo dmesg -C
SJF:
	sudo dmesg -C
	sudo ./main < Input/SJF_1.txt > Output/SJF_1_stdout.txt
	dmesg | grep Project > Output/SJF_1_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/SJF_2.txt > Output/SJF_2_stdout.txt
	dmesg | grep Project > Output/SJF_2_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/SJF_3.txt > Output/SJF_3_stdout.txt
	dmesg | grep Project > Output/SJF_3_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/SJF_4.txt > Output/SJF_4_stdout.txt
	dmesg | grep Project > Output/SJF_4_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/SJF_5.txt > Output/SJF_5_stdout.txt
	dmesg | grep Project > Output/SJF_5_dmesg.txt
	sudo dmesg -C
PJSF:
	sudo dmesg -C
	sudo ./main < Input/PSJF_1.txt > Output/PSJF_1_stdout.txt
	dmesg | grep Project > Output/PSJF_1_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/PSJF_2.txt > Output/PSJF_2_stdout.txt
	dmesg | grep Project > Output/PSJF_2_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/PSJF_3.txt > Output/PSJF_3_stdout.txt
	dmesg | grep Project > Output/PSJF_3_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/PSJF_4.txt > Output/PSJF_4_stdout.txt
	dmesg | grep Project > Output/PSJF_4_dmesg.txt
	sudo dmesg -C
	sudo ./main < Input/PSJF_5.txt > Output/PSJF_5_stdout.txt
	dmesg | grep Project > Output/PSJF_5_dmesg.txt
	sudo dmesg -C
