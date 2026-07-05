from http.server import BaseHTTPRequestHandler, HTTPServer

PORT = 8080

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        body = b"<!DOCTYPE html><html><head><meta charset='utf-8'><title>Hola</title></head><body><h1>\xc2\xa1Hola, Mundo!</h1></body></html>"
        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", len(body))
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, format, *args):
        pass

if __name__ == "__main__":
    server = HTTPServer(("", PORT), Handler)
    print(f"Listening on http://localhost:{PORT}")
    server.serve_forever()
