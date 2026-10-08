

#  0    1    2     3     4    5     6     7     8
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);

#	int  tm_sec;	/* seconds after the minute - [0, 61] */
#			/* for leap seconds */
#	int  tm_min;	/* minutes after the hour - [0, 59] */
#	int  tm_hour;	/* hour since midnight - [0, 23] */
#	int  tm_mday;	/* day of the month - [1, 31] */
#	int  tm_mon;	/* months since January - [0, 11] */
#	int  tm_year;	/* years since 1900 */
#	int  tm_wday;	/* days since Sunday - [0, 6] */
#	int  tm_yday;	/* days since January 1 - [0, 365] */
#	int  tm_isdst;	/* flag for alternate daylight savings time */

$now_year	= $year+1900;
$now_month	= $mon+1;
$now_day	= $mday;

$oline		= sprintf "%04d%02d%02d", $now_year, $now_month, $now_day;
print $oline;
