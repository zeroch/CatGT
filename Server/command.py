import json

class Command:
	LEFT = 0
	RIGHT = 1

def writeCommand2Json(command):
	return json.dumps({'Left':0, 'Right':1, 'Value':command})


test_commands = (0,1,0,0,1,0,0,0)
send_jsons = [writeCommand2Json(command) for command in test_commands]