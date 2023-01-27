FROM ubuntu:latest

# Copy necessary files
COPY . /app
WORKDIR /app

# Install necessary software
RUN apt-get update && \
    apt-get install -y openssh-server python3 python3-pip gunicorn3 nftables && \
    pip3 install flask && \
    apt-get clean
# Configure necessary software
RUN sed 's/#PasswordAuthentication yes/PasswordAuthentication no/' -i /etc/ssh/sshd_config && \
    sed 's/PermitRootLogin prohibit-password/PermitRootLogin no/' -i /etc/ssh/sshd_config

RUN mkdir -p /run/sshd

# Run firewall rules

EXPOSE 22 8000 8001
CMD ["/usr/sbin/sshd", "-D"]
# CMD ["gunicorn3", "app:app", "-b", "0.0.0.0:8000"]

