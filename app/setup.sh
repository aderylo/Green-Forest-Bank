#!bin/bash

# demo account
text1="this is line one\n
this is line two\n
this is line three"

text2="this is line three\n
this is line two\n
this is line one"

# create directories
mkdir credits 
mkdir deposits

echo $text1 > credits/1.txt

echo $text2 > credits/2.txt

# set onwership
chown root credits/1.txt
chown test credits/2.txt

# restric read access to owner
chmod 600 credits/1.txt
chmod 600 credits/2.txt