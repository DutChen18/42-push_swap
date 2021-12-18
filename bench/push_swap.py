import asyncio
import asyncio_process
import os.path

async def sort(path, stack):
	stack = list(map(str, stack))
	stdout, stderr = await asyncio_process.run_exec(
		os.path.join(path, "push_swap"), *stack)
	assert stderr == b""
	return stdout.decode().split("\n")[:-1]

async def check(path, stack, instructions):
	stack = list(map(str, stack))
	instructions = "\n".join(instructions + [""]).encode()
	stdout, stderr = await asyncio_process.run_exec(
		os.path.join(path, "checker"), *stack,
		input=instructions)
	assert stderr == b""
	return stdout == b"OK\n"
