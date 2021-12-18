import asyncio
import push_swap
import sys
import random

INT_MIN = -(2 ** 31)
INT_MAX = 2 ** 31 - 1

async def run(path, index, size):
	stack = random.sample(range(INT_MIN, INT_MAX), size)
	instructions = await push_swap.sort(path, stack)
	status = await push_swap.check(path, stack, instructions)
	instr = len(instructions)

	if status:
		print(f"{index:3}: OK: {instr:5}")
	else:
		print(f"{index:3}: KO")

	return instr

async def main():
	path = sys.argv[1]
	size = int(sys.argv[2])
	count = int(sys.argv[3])
	
	random.seed(0)
	tasks = [run(path, index, size) for index in range(count)]
	results = await asyncio.gather(*tasks)

	r_min = min(results)
	r_avg = sum(results) // len(results)
	r_max = max(results)
	print(f"{r_min} < {r_avg} < {r_max}")

if __name__ == "__main__":
	asyncio.run(main())
