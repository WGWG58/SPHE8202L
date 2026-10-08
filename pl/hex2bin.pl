#! /home/potatooo/xcc/bin/perl

#
# hex2bin.pl
#
# transform a hex (or what-ever) file into binary.
#

$opt_bigendian	= 1;
$opt_short	= 0;
$opt_byte	= 0;

for ($argvcnt=0; $argvcnt<@ARGV && $ARGV[$argvcnt] =~ /^-(.*)/; $argvcnt++)
{
  if ($ARGV[$argvcnt] =~ /^-\z/)
  {
    $argvcnt++;
    last;
  }

  if ($ARGV[$argvcnt] =~ /^--help/
      || $ARGV[$argvcnt] =~ /^-h\z/)
  {
    print("\
Usage: $0 [options] [inputfile [outputfile]]\
\
where option is:\
\
  --little-endian   Specify little-endian output\
  --big-endian      Specify big-endian output (default)\
  --byte            Specify 8-bit output\
  --short           Specify 16-bit output\
  --long            Specify 32-bit output (default)\
\
");
    exit(-1);
  } 
  elsif ($ARGV[$argvcnt] =~ /^--little-endian/)
  {
    $opt_bigendian = 0;
  } 
  elsif ($ARGV[$argvcnt] =~ /^--big-endian/)
  {
    $opt_bigendian = 1;
  } 
  elsif ($ARGV[$argvcnt] =~ /^--short/)
  {
    $opt_short = 1;
    $opt_byte = 0;
  }
   elsif ($ARGV[$argvcnt] =~ /^--byte/)
  {
    $opt_short = 0;
    $opt_byte = 1;
  } 
  elsif ($ARGV[$argvcnt] =~ /^--long/)
  {
    $opt_short = 0;
    $opt_byte = 0;
  }
  else {
    die "$0: illegal option $ARGV[$argvcnt]";
  }
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

$spec = ($opt_bigendian) ? 
          (($opt_byte) ? "C" : (($opt_short) ? "n" : "N")) 
        : (($opt_byte) ? "C" : (($opt_short) ? "v" : "V")) ;

while (<STDIN>)
{
  chop($_);
  $val = hex($_);
  print STDERR "$0: warn: value $_ exceed limit\n" if ($val>255 && $opt_byte);
  print STDERR "$0: warn: value $_ exceed limit\n" if ($val>65535 && $opt_short);
  print STDOUT pack($spec, hex($_))  if ($_ ne "");
}

close(STDIN);
close(STDOUT);

