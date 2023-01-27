#!bin/bash

sudo nft add table inet filter
sudo nft add chain inet filter input { type filter hook input priority 0 \; }
sudo nft add rule inet filter input tcp dport { 22, 443 } accept
sudo nft add rule inet filter input icmp type echo-request accept
sudo nft add rule inet filter input drop