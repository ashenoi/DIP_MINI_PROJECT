1. In order to compile code follow the below steps:
cd test/
make compile

2. To compile the flo code from the middlebury website:
cd test/
make compile_GT

3. In order to run the code and generate the motion vector,
make sim IMAGE=<Name of the image>
The name of the image should be according to the folder name in the test/image folder. Also it assumes that the folders contain frame10.png and frame11.png . In case this need to change make the necessary updates in the sim target in the Makefile.

This will generate mv_<IMAGE>.txt which has all the motion vectors stored in them.
Also if you need to generate the motion vector according to eq 12.
make sim IMAGE=<Name of the image> LAG=1

4. In order to generate the ground truth motiom vector
make extractflow IMAGE<Name of the image>
All the .flo files are present in the Ground_Truth_Files folder
This generates mv_GT_<IMAGE>.txt and contains the Ground thruth.

5.In order to generate the end point error, there is perl script:

perl endpoint_error.pl mv_<IMAGE>.txt mv_GT_<IMAGE>.txt

6. There is also another  script which can be used to measure improvement.

perl results_improvement.pl <file1> <file2>

This gives lines by line improvement in dB

 


In order to execute the code for all images, the steps have been put inside
master.sh

source master.sh OVERLAP=1 produces the results for eq 19
source master.sh LAG=1 produces the results for eq 12

perl results_improvement.pl results_OVERLAP=1.txt results_LAG=1.txt

gives the final improvement
