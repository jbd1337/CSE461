#!/bin/bash

if [ $1 == '-c' ]
then
read -sp "Password: " COOL;
	if [ $2 != '' ]
	then
		ARCHNAME=$2
		7za a -mhe=on -p$COOL "$ARCHNAME.7z" .
	else
		echo "Proper Use is work.bash [-c:compress,-e:extract] filename";
	fi
elif [ $1 == '-e' ]
then
	if [ $2 != '' ]
	then	
		ARCHNAME=$2
		7za e $ARCHNAME
	else
		echo "Proper Use is work.bash [-c:compress,-e:extract] filename";
	fi
else
	echo "Proper Use is work.bash [-c:compress,-e:extract] filename";
fi
exit
