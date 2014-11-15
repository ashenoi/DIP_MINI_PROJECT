export SRC := ../src
export FILE := main_journal
export IMAGE ?= Dimetrodon

compile: clean
	g++ -ggdb `pkg-config --cflags opencv` -o out.o ../src/pair_motion.cpp ../src/main_journal.cpp -I../src `pkg-config --libs opencv`

clean:
	rm -fr motion_vectors.txt out.o
sim:
	./out.o ./images/${IMAGE}/frame10.png ./images/${IMAGE}/frame11.png
	cp -f motion_vectors.txt mv_${IMAGE}.txt

run: compile sim

compile_GT: 
	cd $(SRC)/flow-code/imageLib && make
	cd $(SRC)/flow-code && make

extractflow:
	./$(SRC)/flow-code/color_flow ./Ground_Truth_Files/${IMAGE}/flow10.flo mv_GT_${IMAGE}.txt	
