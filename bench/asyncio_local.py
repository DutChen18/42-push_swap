import asyncio

class local:
	def __init__(self):
		self.context = {}

	def get_it(self):
		loop = id(asyncio.get_running_loop())
		return self.context[loop]
	
	def set_it(self, value):
		loop = id(asyncio.get_running_loop())
		self.context[loop] = value
	
	def del_it(self):
		loop = id(asyncio.get_running_loop())
		del self.context[loop]

	def get(self, init):
		loop = id(asyncio.get_running_loop())
		if loop not in self.context:
			return init()
		return self.context[loop]

	def set(self, init):
		loop = id(asyncio.get_running_loop())
		if loop not in self.context:
			self.context[loop] = init()
		return self.context[loop]
