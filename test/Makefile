export SRC := ../src
export FILE := main_journal
compile:
	g++ -ggdb `pkg-config --cflags opencv` -o out.o ../src/pair_motion.cpp ../src/main_journal.cpp -I../src `pkg-config --libs opencv`
