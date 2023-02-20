# Green-Forest-Bank: Part 1 

Implementation of a simple application for handling loans and deposits at Green Forest Bank. Part of Computer System Secuirty course at MIMUW. 

## Setup 
Run setup script:
```
bash setup.sh 
```

## Build 
Compile application (setup script should create build directory by itself)
```
cd build 
cmake .. 
make
```

## Run
In build directory:  
```
./main
```

# Green-Forest-Bank: Part 2 

## Container 
To build containerized application:
```
cd app
docker build -t app . 
```

To run it: 
```
docker run -p 22:22 -p 443:443 app 
```
App will be served on 443 port (https://host) and one can connect to a container via ssh in following manner "ssh root@host". 
For example, to connect with an app from a localhost https://0.0.0.0 should suffice.  

## Demo
Furthermore, Dockerfile creates two users to demonstrate webapp ability to restrict view for a given user to view files they own. Using app/setup.sh script it creates two credit files `credits/1.txt`, `credits/2.txt` and sets ownership to `root` user for the first one and for the second one to user called `test`.  When logging with following credentials one can look up `credits/1.txt` contents, since root user is an owner of this file: 
```
username: root
password: password
```

However, when using credentials of the seconder user:
```
username: test
password: pass
```
Contents of `credits/1.txt` will not be displayed and it will only show the insides of the `credits/2.txt` file. 

## Firewall 
In order to apply firewall rules using nft run following command with root privileges: 
```
bash sudo firewall.sh
```

