#!/bin/bash
# Required package: jq

ps_user=`jq '.username' dist.conf | tr -d \"`
db_name=`jq '.db_name' dist.conf | tr -d \"`
pwd=`pwd`

createdb -U $ps_user $db_name

cd ../scripts/update

files=`ls -r update_*.sql | sort`
for VAR in $files
do
    psql -U $ps_user -d $db_name -f $VAR 
done

cd $pwd