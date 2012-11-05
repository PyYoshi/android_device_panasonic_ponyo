#Yuhaipeng 20110919
#This scripts send iptables to 3G network device rmnet0 to filter icmp request from 3G net

logi ()
{
  /system/bin/log -t $LOG_TAG -p e "$LOG_NAME $@"
}

logi "Set iptables rules for network security."

iptables -D INPUT -i rmnet0 -p icmp --icmp-type echo-reply                -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type destination-unreachable   -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type source-quench             -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type redirect                  -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type time-exceeded             -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type parameter-problem         -j ACCEPT
iptables -D INPUT -i rmnet0 -p icmp --icmp-type any                       -j DROP


iptables -A INPUT -i rmnet0 -p icmp --icmp-type echo-reply                -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type destination-unreachable   -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type source-quench             -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type redirect                  -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type time-exceeded             -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type parameter-problem         -j ACCEPT
iptables -A INPUT -i rmnet0 -p icmp --icmp-type any                       -j DROP

