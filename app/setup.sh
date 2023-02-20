#!bin/bash

# demo account
text="this is line one\n
this is line two\n
this is line three"

# create directories
mkdir credits 
mkdir deposits

echo $text > credits/1.txt
chmod 600 credits/1.txt