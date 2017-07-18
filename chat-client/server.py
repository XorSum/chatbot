# coding = "utf-8"
# 用于测试udp协议能否正常工作
import socket  

url = '127.0.0.1'
port = 8082
address = (url,port)  
str="I am your father"

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
s.bind(address)  
 
while True:  
    data, addr = s.recvfrom(2048)  
    if not data:  
        print("new client ")    
    print("received:", data.decode("utf-8"), "from", addr)
    s.sendto(('%s\r\n' % str).encode(),addr)

s.close()  
