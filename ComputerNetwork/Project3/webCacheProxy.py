import socket
import threading
import signal
import sys
import os
from urllib.request import Request, urlopen, HTTPError

config = {
    "HOST_NAME" : "127.0.0.1",
    "BIND_PORT" : 12345,
    "MAX_REQUEST_LEN" : 1024,
    "CONNECTION_TIMEOUT" : 5
}

'''
Proxy Functionality
    1. The proxy listens for requests from clients
    2. When there is a request, the proxy spawns a new thread for handling the request
    and creates an HttpRequest-object which contains the request.
    3. The new thread sends the request to the server and reads the server’s reply into an HttpResponse-object.
    4. The thread sends the response back to the requesting client.

'''

class Server:
    # Initiation Part
    def __init__(self, config):
        signal.signal(signal.SIGINT, self.shutdown)
        self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.serverSocket.bind((config['HOST_NAME'], config['BIND_PORT']))
        self.serverSocket.listen(10)
        self.__clients = {}
        print("init")

    # Connection Part
    def listenForClient(self):
        # get connection from client
        while True:
            (clientSocket, client_address) = self.serverSocket.accept()
            d = threading.Thread(name=self._getClientName(client_address), target=self.proxy_thread, args=(clientSocket, client_address))
            d.setDaemon(True)
            d.start()
        self.shutdown(0,0)

    def proxy_thread(self, conn, client_addr):
        # get request from browser
        request = conn.recv(config['MAX_REQUEST_LEN'])
        dec_request = request.decode("utf-8")
        # parse
        first_line = dec_request.split('\n')[0]
        url = first_line.split(' ')[1]

        print("First: ", first_line)
        print("URL: ", url)

        # find the webserver and port
        http_pos = url.find("://")
        if http_pos == -1:
            temp = url
        else:
            temp = url[(http_pos+3):]

        port_pos = temp.find(":")

        # find end of web server
        webserver_pos = temp.find("/")
        if webserver_pos == -1:
            webserver_pos = len(temp)
        
        webserver = ""
        port = -1
        if (port_pos==-1 or webserver_pos<port_pos):
            port = 80
            webserver = temp[:webserver_pos]
        else:
            port = int((temp[(port_pos+1):])[:webserver_pos-port_pos-1])
            webserver = temp[:port_pos]

        filename = temp[webserver_pos:]

        # Index check
        if filename == '/':
            filename = '/index.html'

        print(filename)

        # Get the file

        try:
            # Check if we have this file locally
            fin = open('cache/' + webserver + filename)
            content = fin.read()
            fin.close()
            # If we have it, let's send it
        except IOError:
            content = None

        if content:
            print('Fetched successfully from cache.')
            conn.sendall(content.encode())
            conn.close()

        else:
            print('Not in cache. Fetching from server.')

            try:
                # create a socket to connect to the web server
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.settimeout(config['CONNECTION_TIMEOUT'])
                s.connect((webserver, port))
                # send request to webserver
                print("Request: ", request.decode("utf-8"))
                s.sendall(request)
               
                real_file_pos = filename.rfind('/')
                path = filename[:real_file_pos]
                real_filename = filename[real_file_pos:]
                if not os.path.isdir('./cache/'+ webserver + path):
                    os.mkdir('./cache/'+ webserver + path)
                cached_file = open('./cache/' + webserver + filename, "w+b")

                while 1:
                    # receive data
                    content = s.recv(config['MAX_REQUEST_LEN'])
                    # send to browser
                    if (len(content)>0):
                        conn.send(content)
                        # save_in_cache(filename, content)
                        print('Saving a copy of {} in the cache'.format(filename))
                        cached_file.write(content)
                    else:
                        break

                cached_file.close()
                s.close()
                conn.close()

            except socket.error as error_msg:
                print('ERROR: ', client_addr, error_msg)
                if s:
                    s.close()
                if conn:
                    conn.close()
                print("Runtime Error:", error_msg)
                sys.exit(1)

            # q = Request(url)

            # try:
            #     response = urlopen(q)
            #     # Grab the header and content from the server req
            #     response_headers = response.info()
            #     content = response.read()
                # if content:
                #     # save_in_cache(filename, content)
                #     print('Saving a copy of {} in the cache'.format(filename))
                #     real_file_pos = filename.rfind('/')
                #     path = filename[:real_file_pos]
                #     real_filename = filename[real_file_pos:]
                #     if not os.path.isdir('./cache'+path):
                #         os.mkdir('./cache'+path)
                #     # os.makedirs(os.path.dirname(path), exist_ok = True)
                #     cached_file = open('./cache' + filename, "w+b")
                #     cached_file.write(content)
                #     cached_file.close()
            # except HTTPError:
            #     content = None

        # If we have the file, return it, otherwise 404
        # if content:
        #     temp = 'HTTP/1.0 200 OK\n\n'
        #     send_response = b'HTTP/1.0 200 OK\n\n' + content
        # else:
            # temp = 'HTTP/1.0 404 NOT FOUND\n\n File Not Found'
        #     send_response = b'HTTP/1.0 404 NOT FOUND\n\n File Not Found'

        # Send the response and close the connection
            # if content:
            #     conn.sendall(content)
            # else:
            #     temp = 'HTTP/1.0 404 NOT FOUND\n\n File Not Found'
            #     conn.sendall(temp.encode())

    def _getClientName(self, cli_addr):
        return "Client"

    def shutdown(self, signum, frame):
        self.serverSocket.close()
        sys.exit(0)

    '''
    TO DO :
        1. Better error handling (error -> just stop processing, client will get timeout)
        2. Support for POST-method
        3. Add caching
            1) When the proxy gets a request, it checks of the requested object is cached, and if yes,
            then returns the object from the cache, without contacting the server.
            2. If the object is not cached, the proxy retrieves the object from the server, returns it to the client,
            and caches a copy for future requests.
    '''

if __name__ == "__main__":
    server = Server(config)
    try:
    	server.listenForClient()
    except KeyboardInterrupt:
    	print("Ctrl C - Stopping server")
    sys.exit(1)