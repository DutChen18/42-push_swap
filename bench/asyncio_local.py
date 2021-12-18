import asyncio

class local:
	def __init__(self, init):
		self.context = {}
		self.init = init

	def get(self, init=None):
		loop = id(asyncio.get_running_loop())
		if loop not in self.context:
			self.context[loop] = (init or self.init)()
		return self.context[loop]
