open(FILE1,"<$ARGV[0]") or die("Could not open");
open(FILE2,"<$ARGV[1]") or die("Could not open");

$count=0;
$EE=0;
while($line1=<FILE1>)
{
	$line2 = <FILE2>;
	chomp($line1);
	chomp($line2);
	@mv1 = split(',',$line1);
	@mv2 = split(',',$line2);
	if( $mv2[0] >= 1000000000 or $mv2[1] >= 1000000000)
	{
		next;
	}
	$EE+=(($mv1[0]-$mv2[0])**2+($mv1[1]-$mv2[1])**2)**0.5;
	$count+=1;
}
$EE=$EE/$count;
print $EE,"\n";
close(FILE1);
close(FILE2);
