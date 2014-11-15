export SRC := ../src
export FILE := main_journal


compile: clean
	g++ -ggdb `pkg-config --cflags opencv` -o out.o ../src/pair_motion.cpp ../src/main_journal.cpp -I../src `pkg-config --libs opencv`

clean:
	rm -fr motion_vectors.txt out.o
sim:
	./out.o

run: compile sim
