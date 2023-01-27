FROM ubuntu:latest

COPY . /app
WORKDIR /app

# Install dependencies 
RUN apt-get update && apt-get install -y openssh-server python3 python3-pip gunicorn supervisor nftables
RUN pip3 install -r requirements.txt

# Create a directory for the ssh server to store its host keys
RUN mkdir /var/run/sshd

RUN echo 'root:password' | chpasswd

# Allow root login via ssh 
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

EXPOSE 22 443
CMD ["/usr/bin/supervisord"]