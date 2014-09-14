import sys

g_Scenegraph = None

def ExposeScenegraph(cxxRef):
	global g_Scenegraph
	g_Scenegraph = cxxRef

class OutputRedirector(object):
	def write(self, message):
		glove.Log(message)
		
sys.stdout = OutputRedirector()

blooob = "test2"