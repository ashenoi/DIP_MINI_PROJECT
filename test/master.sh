make compile $1
make sim IMAGE=Dimetrodon 
make sim IMAGE=Grove2 
make sim IMAGE=Grove3 
make sim IMAGE=Hydrangea 
make sim IMAGE=RubberWhale 
make sim IMAGE=Urban2 
make sim IMAGE=Urban3 
make sim IMAGE=Venus
#make compile_GT
#make extractflow IMAGE=Dimetrodon 
#make extractflow IMAGE=Grove2 
#make extractflow IMAGE=Grove3 
#make extractflow IMAGE=Hydrangea 
#make extractflow IMAGE=RubberWhale 
#make extractflow IMAGE=Urban2 
#make extractflow IMAGE=Urban3 
#make extractflow IMAGE=Venus

perl endpoint_error.pl mv_Dimetrodon.txt mv_GT_Dimetrodon.txt | tee results_$1\.txt
perl endpoint_error.pl mv_Grove2.txt mv_GT_Grove2.txt >> results_$1\.txt
perl endpoint_error.pl mv_Grove3.txt mv_GT_Grove3.txt >> results_$1\.txt
perl endpoint_error.pl mv_Hydrangea.txt mv_GT_Hydrangea.txt >> results_$1\.txt
perl endpoint_error.pl mv_RubberWhale.txt mv_GT_RubberWhale.txt >> results_$1\.txt
perl endpoint_error.pl mv_Urban2.txt mv_GT_Urban2.txt >> results_$1\.txt
perl endpoint_error.pl mv_Urban3.txt mv_GT_Urban3.txt >> results_$1\.txt
perl endpoint_error.pl mv_Venus.txt mv_GT_Venus.txt >> results_$1\.txt
