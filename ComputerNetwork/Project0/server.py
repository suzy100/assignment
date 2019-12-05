import socket
import threading

def send(sock):
	while True:
		sendData = input('> ')
		sock.send(sendData.encode('utf-8'))

def receive(sock):
	while True:
		recvData = sock.recv(65535)
		print(client_id, "(", addr[0], addr[1], ") : ", recvData.decode('utf-8'))

port = 8080

ip = input("IP : ")
port = int(input("Port : "))

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind((ip, port))
server_socket.listen(0)

client_socket,addr = server_socket.accept()

client_id = client_socket.recv(65535)
client_id = client_id.decode('utf-8')

sender = threading.Thread(target=send, args=(client_socket,))
receiver = threading.Thread(target=receive, args=(client_socket,))
sender.start()
receiver.start()

while 1:
	pass