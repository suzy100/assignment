from http.server import BaseHTTPRequestHandler, HTTPServer
from socketserver import ThreadingMixIn

class ThreadingServer(ThreadingMixIn, HTTPServer):
	pass

class MyHandler(BaseHTTPRequestHandler):

	protocol_version = 'HTTP/1.1'

	def do_GET(self):

		# error 400 Bad Request
		if self.protocol_version != self.request_version:
			self.send_error(400)
			return

		# if self.path=="/":
		# 	f = open(curdir)

		try:
			sendReply = False

			# jpg
			if self.path.endswith('.jpg'):
				content_type = 'image/jpg'
				sendReply = True

			# html
			if self.path.endswith('.html'):
				content_type = 'text/html'
				sendReply = True
			
			if sendReply == True:
				f = open("." + self.path)
				self.send_response(200)
				self.send_header('Content-type',content_type)
				self.send_header('Content-Length',1024)
				self.end_headers()
				f.close()				

			return

		# error 404 Not found
		except IOError:
			self.send_error(404)

try:
	# Thread
	server = ThreadingServer(('',8961), MyHandler)
	print('Started WebServer on port 8961')
	print('Press Ctrl + c to quit webserver')
	server.serve_forever()

except KeyboardInterrupt:
	print('Shutting down WebServer')
	server.socket.close()