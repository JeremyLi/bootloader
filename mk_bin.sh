#!/bin/bash
if [ -d $1 ]
then
    echo $1 exist!
else
    echo  creating $1 dir!
    mkdir $1
fi

