import asyncio
import asyncio_process
import os.path

def opt_join(d, b):
	if b is None:
		return d
	return os.path.join(d, b)

async def sort(path, stack, exe="push_swap"):
	stack = list(map(str, stack))
	stdout, stderr = await asyncio_process.run_exec(
		opt_join(path, exe), *stack)
	assert stderr == b""
	return stdout.decode().split("\n")[:-1]

async def check(path, stack, instructions, exe="checker"):
	stack = list(map(str, stack))
	instructions = "\n".join(instructions + [""]).encode()
	stdout, stderr = await asyncio_process.run_exec(
		opt_join(path, exe), *stack,
		input=instructions)
	assert stderr == b""
	return stdout == b"OK\n"
