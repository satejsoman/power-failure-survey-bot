import json
import socket
from datetime import datetime
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path

from twilio.rest import Client

with (Path(__file__).parent / ".creds").open() as f:
    creds = json.load(f)
client = Client(creds['TWILIO_LIVE_ACCOUNT_SID'], creds['TWILIO_LIVE_AUTH_TOKEN'])

# print IPs
from requests import get

ip = get('https://api.ipify.org').content.decode('utf8')
print(f'public IP address: {ip}')

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
print(f'private IP address: {s.getsockname()[0]}')
s.close()

def send_message():
    message = client.messages.create(
        from_ = creds["TWILIO_SENDER_NUMBER"],
        body  = f"test! {datetime.now()}",
        to    = creds["TWILIO_RECIPIENT_NUMBER"]
    )
    return message.sid

class PowerFailureBotServer(BaseHTTPRequestHandler):
    def do_POST(self):
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()

        send_message()

        message = "Hello, World! Here is a POST response"
        self.wfile.write(bytes(message, "utf8"))

with HTTPServer(('', 80), PowerFailureBotServer) as server:
    server.serve_forever()
