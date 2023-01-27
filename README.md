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
docker run -p 22:22 -p 8000:8000 app 
```
App will be served on 8000 port and one can connect with root user via ssh root@host. 

## Firewall 
In order to apply firewall rules using nft run following command with root privileges: 
```
bash sudo firewall.sh
```

