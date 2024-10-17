import requests as req
import sys

# Pushover API credentials
api_token = "agrb5bsit9t4cdhqscengb5x7kx8w3"
user_key = "udnve2vgdrd9y94wd8eerso5fmyjyd"

def send_notification(message):
	url = "https://api.pushover.net/1/messages.json"
	payload =
	{
		"token": api_token,
		"user": user_key,
		"message": message
	}
	response = req.post(url, data=payload)

	if response.status_code == 200:
		print("Notification sent successfully.")
	else:
		print("Failed to send notification:", response.text)

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print("Usage: python push.py <message>")
		sys.exit(1)

	send_notification(sys.argv[1])
