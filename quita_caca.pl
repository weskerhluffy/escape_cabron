#!/usr/bin/perl
# XXX: http://www.softpanorama.org/Scripting/Perlbook/Ch04/using_record_separator.shtml
# XXX: http://docstore.mik.ua/orelly/perl3/cookbook/ch06_07.htm
#$/ = ";";
$/ = "";
$mierda="src/main.c";
open QUOTES, "$mierda" or die " can't open $mierda. ReasonL $!";
while(<QUOTES>)
{
	s{
        (                   # capture in $1
	caca_log_debug
	.*?;
        )
    }{}gxsm;
#    }{<H1>$1</H1>}gxsm;
	print;
}

#@file = <QUOTES>;
#$random = rand(@file);
#$fortune = $file[$random];
#chomp $fortune; # remove a single character record separator on the end 
#print "$fortune\n";
