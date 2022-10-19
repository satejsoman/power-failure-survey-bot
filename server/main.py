import json
from pathlib import Path
from datetime import datetime

from twilio.rest import Client

if __name__ == "__main__":
    with (Path(__file__).parent / ".creds").open() as f:
        creds = json.load(f)
    client = Client(creds['TWILIO_LIVE_ACCOUNT_SID'], creds['TWILIO_LIVE_AUTH_TOKEN'])

    message = client.messages.create(
        from_ = creds["TWILIO_SENDER_NUMBER"],
        body  = f"test! {datetime.now()}",
        to    = creds["TWILIO_RECIPIENT_NUMBER"]
    )

    print(message.sid)
