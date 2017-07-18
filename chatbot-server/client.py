# coding = "utf-8"
# 用于测试udp协议能否正常工作
import socket  
import sys
  
url = '127.0.0.1'
port = 8084
address = (url,port)  

rurl = '127.0.0.1'
rport=8082
raddress=(rurl,rport)

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
s.bind(address) 

while True:  
    print('please input:')
    msg = input()
    s.sendto(('%s' % msg).encode(), raddress)  
    data,addr = s.recvfrom(2048)
    print(data.decode("utf-8"))
s.close()
