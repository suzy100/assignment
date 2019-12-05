import requests
import urllib.request
import os

user_agent = ""

def get(url):
	# headers = {'User-Agent': 'ComputerNetwork'}
	headers = {'User-Agent': user_agent}
	response = requests.get(url = url, headers = headers)
	response.encoding = 'utf-8'
	print(response.status_code,response.text)

def post(url, data):
	# headers = {'User-Agent': 'ComputerNetwork'}
	headers = {'User-Agent': user_agent}
	response = requests.post(url = url, headers = headers, data=data)
	response.encoding = 'utf-8'
	print(response.status_code,response.text)

def img(url):
	curdir = os.getcwd()
	print("saving in "+curdir)
	file = "\\test.jpg"
	urllib.request.urlretrieve(url, curdir+file)
	print("complete!")

while(1):
	method = input("method: ")
	url = input("url: ")
	user_agent = input("User-Agent: ")
	if (method=="GET"):
		get(url)
	elif (method=="POST"):
		data = input("data: ")
		post(url, data)
	elif (method=="IMG"):
		img(url)
	else:
		print("Wrong input.")