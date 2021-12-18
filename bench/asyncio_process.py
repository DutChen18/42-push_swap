import asyncio
import asyncio_local

sem = asyncio_local.local(lambda: asyncio.Semaphore(50))

class proc_exec:
	def __init__(self, *args, **kwargs):
		self.args = args
		self.kwargs = kwargs

	async def __aenter__(self):
		await sem.get().acquire()
		return await asyncio.create_subprocess_exec(*self.args, **self.kwargs)
	
	async def __aexit__(self, exc_type, exc_value, traceback):
		sem.get().release()

async def run_exec(program, *args, input=None):
	context = proc_exec(program, *args,
		stdin=asyncio.subprocess.PIPE,
		stdout=asyncio.subprocess.PIPE,
		stderr=asyncio.subprocess.PIPE)
	async with context as proc:
		return await proc.communicate(input)
