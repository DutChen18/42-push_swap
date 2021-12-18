#!/usr/bin/env python3
import asyncio
import random
import matplotlib.pyplot as plt

async def pexec(*args, **kwargs):
	async with pexec.sem:
		proc = await asyncio.create_subprocess_exec(*args,
			stdout=asyncio.subprocess.PIPE,
			stdin=asyncio.subprocess.PIPE)
		stdout, stderr = await proc.communicate(kwargs.get("stdin"))
		return stdout

async def sort(stack):
	stdout = await pexec("./push_swap", *map(str, stack))
	#print(len(stack))
	return stdout.decode().split("\n")[:-1]

async def check(stack, solution):
	solution = "\n".join(solution + [""]).encode()
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

async def plot2(n, m, c, ax, j):
	await pexec("make", "re", f"CFLAGS=-DCHUNK_SIZE={c}")
	stacks = [list(range((i+1)*m)) for i in range(n)]
	for stack in stacks:
		random.shuffle(stack)
	counts = [0 for _ in range(n)]
	for _ in range(j):
		sol = await asyncio.gather(*map(sort, stacks))
		for i in range(n):
			counts[i] += len(sol[i]) / j
	ax.plot([(i+1)*m for i in range(n)], counts, linewidth=2.0)

async def plot(n, m, j):
	pexec.sem = asyncio.Semaphore(100)
	fig, ax = plt.subplots()
	for c in [150]:
		await plot2(n, m, c, ax, j)
	plt.show()

if __name__ == "__main__":
	random.seed(0)
	asyncio.run(main())
	#asyncio.run(plot(500, 1, 1))
