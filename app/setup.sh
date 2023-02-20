#!bin/bash

# setup demo users and their credentials
RUN useradd test
RUN echo 'root:password' | chpasswd
RUN echo 'test:pass' | chpasswd

# demo account
text="this is line one\n
this is line two\n
this is line three"

# create directories
mkdir credits 
mkdir deposits

echo $text > credits/1.txt