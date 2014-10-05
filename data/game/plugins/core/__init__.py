# The test component should print yay to the console
class TestComponent(GameComponent):
	def __init__(self):
		GameComponent.__init__(self)
		self.up = True

	def SyncUpdate(self):
		if(self.up):
			print("yay")
			self.up = False

def LoadPlugin():
	cam = g_Scenegraph.CreateCamera()
	g_Scenegraph.SetActiveCamera(cam)
	
	go = g_Scenegraph.CreateGameObject()
	go.AddComponent(TestComponent())