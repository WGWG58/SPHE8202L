
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

$when = time();

for (; $argvcnt<@ARGV; $argvcnt++)
{
  utime($when, $when, <$ARGV[$argvcnt]>);
}


