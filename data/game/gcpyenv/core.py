import sys

class OutputRedirector(object):
	def write(self, message):
		Log(message)
		
sys.stdout = OutputRedirector()