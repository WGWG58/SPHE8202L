#! /home/potatooo/xcc/bin/perl

#
# FILE
# wecho.pl
#
# DESCRIPTION
# humm... avoid DOS-WIN32 builtin ECHO bug
#

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
  else {
    die "$0: illegal option $ARGV[$argvcnt]";
  }
}


for (; $argvcnt<@ARGV; $argvcnt++)
{
  print $ARGV[$argvcnt] . " ";
}
print "\n";

