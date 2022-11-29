import os

from datetime import datetime

from twilio.rest import Client as TwilioClient

TWILIO_LIVE_ACCOUNT_SID = os.getenv("TWILIO_LIVE_ACCOUNT_SID")
TWILIO_LIVE_AUTH_TOKEN  = os.getenv("TWILIO_LIVE_AUTH_TOKEN")
TWILIO_RECIPIENTS       = os.getenv("TWILIO_RECIPIENTS")
TWILIO_SENDER_NUMBER    = os.getenv("TWILIO_SENDER_NUMBER")

twilio_client = TwilioClient(TWILIO_LIVE_ACCOUNT_SID, TWILIO_LIVE_AUTH_TOKEN)

def forward_message(request):
    """Responds to any HTTP request.
    Args:
        request (flask.Request): HTTP request object.
    Returns:
        The response text or any set of values that can be turned into a
        Response object using
        `make_response <http://flask.pocoo.org/docs/1.0/api/#flask.Flask.make_response>`.
    """
    message_IDs = []
    for recipient in TWILIO_RECIPIENTS.split("|"):
        message = twilio_client.messages.create(
            from_ = TWILIO_SENDER_NUMBER,
            body  = f"Hello! We detected a power failure at {datetime.now()}. Can you help us understand what happened? https://forms.gle/5WM8gz3BEamNaBxTA",
            to    = recipient
        )
        message_IDs.append(message.sid)
    return f"message IDs: {message_IDs}"
