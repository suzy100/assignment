import socket
import threading

def send(sock):
	while True:
		sendData = input('> ')
		sock.send(sendData.encode('utf-8'))

def receive(sock):
	while True:
		recvData = sock.recv(65535)
		print("Server : ", recvData.decode('utf-8'))

host = ''
port = 8080

client_id = input("ID : ")
host = input("Host(IP) : ")
port = int(input("Port : "))

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((host, port))
socket.send(client_id.encode('utf-8'))

sender = threading.Thread(target=send, args=(socket,))
receiver = threading.Thread(target=receive, args=(socket,))

sender.start()
receiver.start()

while 1:
	pass