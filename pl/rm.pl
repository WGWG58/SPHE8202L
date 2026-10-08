
#
#
#

for ($argvcnt=0; $argvcnt<@ARGV && $ARGV[$argvcnt] =~ /^-(.*)/; $argvcnt++)
{
  if ($ARGV[$argvcnt] =~ /^-\z/)
  {
    $argvcnt++;
    last;
  }
  
}

for (; $argvcnt<@ARGV; $argvcnt++)
{
  unlink <$ARGV[$argvcnt]>;
}


