source master.sh OVERLAP=1
source master.sh LAG=1

perl results_improvement.pl results_OVERLAP=1.txt results_LAG=1.txt | tee Final_improvement.txt
