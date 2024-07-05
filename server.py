from http.server import SimpleHTTPRequestHandler, HTTPServer
import subprocess
import urllib.parse

class CustomHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/' or self.path == '/server.html':
            self.path = '/server.html'
            return super().do_GET()
        elif self.path.startswith('/?cmd='):
            command = urllib.parse.unquote(self.path[6:])
            try:
                result = subprocess.check_output(command, shell=True, text=True)
                self.send_response(200)
                self.send_header('Content-type', 'text/plain')
                self.end_headers()
                self.wfile.write(result.encode())
            except subprocess.CalledProcessError as e:
                self.send_response(500)
                self.send_header('Content-type', 'text/plain')
                self.end_headers()
                self.wfile.write(f"Error: {e}".encode())
        else:
            self.send_error(404, "File Not Found")

def run(server_class=HTTPServer, handler_class=CustomHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Serving on port 8000")
    httpd.serve_forever()

if __name__ == '__main__':
    run()

