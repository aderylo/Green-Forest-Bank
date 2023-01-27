FROM ubuntu:latest

# install openssh-server and sudo
RUN apt-get update && apt-get install -y openssh-server sudo

# create a new user named 'test'
RUN useradd -rm -d /home/test -s /bin/bash -g root -G sudo -u 1000 test

# set the password for the 'test' user
RUN echo 'test:test' | chpasswd

# create a directory for the ssh server to store its host keys
RUN mkdir /var/run/sshd

# allow password based authentication
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/g' /etc/ssh/sshd_config

# expose port 22 for ssh
EXPOSE 22

# start the ssh service
CMD ["/usr/sbin/sshd", "-D"]