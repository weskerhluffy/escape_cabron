#!/bin/sh -x
# XXX: http://stackoverflow.com/questions/14350856/can-awk-patterns-match-multiple-lines
#cat $1 |awk 'BEGIN {RS=";"} !/caca_log/ {print}' > $1.tmp
perl quita_caca.pl $1 > $1.tmp
cp -fv $1.tmp  $1
