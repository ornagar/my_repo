from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import os

class KodeFunHTTPRequestHandler(BaseHTTPRequestHandler):
	def do_GET(self):
		rootdir = '~/my_repo/my_repo/src/python/'
		try:
			if self.path.endswith('.html'):
				f = open(rootdir + self.path)
				self.send_response(200)
				
				self.send_header('Content-type', 'text-html')
				self.end_headers()
				
				self.wfile.write(f.read())
				f.close()
				return
		except IOError:
			self.send_error(404, 'file not found')
			
		
def run():
	print('http server is starting...')
	
	#ip and port of server
	#by default http server port is 80
	server_address = ('127.0.0.1', 80)
	httpd = HTTPServer(server_address, KodeFunHTTPRequestHandler)
	print('http server is running...')
	httpd.serve_forever()
	
if __name__ == '__main__':
	run()
