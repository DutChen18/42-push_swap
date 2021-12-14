#!/usr/bin/env python3
import asyncio
import random

async def sort(stack):
	proc = await asyncio.create_subprocess_exec(
		"./push_swap", *map(str, stack),
		stdout=asyncio.subprocess.PIPE)
	stdout, stderr = await proc.communicate()
	return stdout.decode()[:-1].split('\n')

async def check(stack, solution):
	proc = await asyncio.create_subprocess_exec(
		"./checker", *map(str, stack),
		stdout=asyncio.subprocess.PIPE,
		stdin=asyncio.subprocess.PIPE)
	solution = "\n".join(solution).encode() + b"\n"
	stdout, stderr = await proc.communicate(solution)
	return stdout == b"OK\n"

async def main():
	stacks = [list(range(500)) for _ in range(100)]
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
	asyncio.run(main())
