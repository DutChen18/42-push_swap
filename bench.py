#!/usr/bin/env python3
import asyncio
import random

async def pexec(*args, **kwargs):
	async with pexec.sem:
		proc = await asyncio.create_subprocess_exec(*args,
			stdout=asyncio.subprocess.PIPE,
			stdin=asyncio.subprocess.PIPE)
		stdout, stderr = await proc.communicate(kwargs.get("stdin"))
		return stdout

async def sort(stack):
	stdout = await pexec("./push_swap", *map(str, stack))
	return stdout.decode()[:-1].split('\n')

async def check(stack, solution):
	solution = "\n".join(solution).encode() + b"\n"
	stdout = await pexec("./checker", *map(str, stack), stdin=solution)
	return stdout == b"OK\n"

async def main():
	pexec.sem = asyncio.Semaphore(100)
	stacks = [list(range(500)) for _ in range(200)]
	for stack in stacks:
		random.shuffle(stack)
	solutions = await asyncio.gather(*map(sort, stacks))
	results = await asyncio.gather(*[check(s, r) for s, r in zip(stacks, solutions)])
	counts = list(map(len, solutions))
	print(f"min: {min(counts)}")
	print(f"max: {max(counts)}")
	print(f"avg: {sum(counts) // len(counts)}")
	print(f"ok: {all(results)}")

if __name__ == "__main__":
	random.seed(0)
	asyncio.run(main())
