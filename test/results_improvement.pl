open(FILE1,"<$ARGV[0]") or die("Could not open");
open(FILE2,"<$ARGV[1]") or die("Could not open");

while($line1=<FILE1>)
{
	$line2=<FILE2>;
	chomp($line1);
	chomp($line2);
	print 10*log10(($line2/$line1)),"\n";

}
sub log10 {
    my $n = shift;
    return log($n)/log(10);
}
