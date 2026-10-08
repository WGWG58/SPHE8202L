#! /home/potatooo/xcc/bin/perl

#
# makedep.pl
#

for ($argvcnt=0; $argvcnt<@ARGV && $ARGV[$argvcnt] =~ /^-(.*)/; $argvcnt++)
{
  if ($ARGV[$argvcnt] =~ /^-\z/)
  {
    $argvcnt++;
    last;
  }
  die "$0: illegal option $ARGV[$argvcnt]";
}


if ($argvcnt<@ARGV) {
  open(STDIN, "<$ARGV[$argvcnt]") || die "$0: err: can't open $ARGV[$argvcnt]";
  $argvcnt++;
}
if ($argvcnt<@ARGV) {
  open(STDOUT, ">$ARGV[$argvcnt]") || die "$0: err: can't open $ARGV[$argvcnt]";
  $argvcnt++;
}

#set output to binary mode
binmode STDOUT;

while (<STDIN>)
{
  s/^(.*)\.o\s*\:\s*(.*)/MIPS\/\1.o MIPS\/\1.d : \\\n \2/g ;
  print $_;
}

close(STDIN);
close(STDOUT);

