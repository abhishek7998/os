#! /bin/bash
echo "Marks: $1"
if [ $1 -ge 90 ]
then
    echo "grade A"
elif [ $1 -ge 70 ]
   then
    echo "grade B"
elif [ $1 -ge 40 ]
   then
    echo "grade c"
else
    echo "fail"
 fi
