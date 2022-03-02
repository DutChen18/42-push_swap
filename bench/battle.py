import asyncio
import push_swap
import sys
import random
import os.path

INT_MIN = -(2 ** 31)
INT_MAX = 2 ** 31 - 1

async def run(ps1, ps2, index, size):
	stack = random.sample(range(INT_MIN, INT_MAX), size)
	instr1 = await push_swap.sort(ps1, stack, exe=None)
	instr2 = await push_swap.sort(ps2, stack, exe=None)
	len1 = len(instr1)
	len2 = len(instr2)

	if len1 < len2:
		print(f"\033[32m{len1:{width}} \033[31m{len2:{width}}\033[0m")
	elif len2 < len1:
		print(f"\033[31m{len1:{width}} \033[32m{len2:{width}}\033[0m")
	else:
		print(f"\033[33m{len1:{width}} \033[33m{len2:{width}}\033[0m")

async def main():
	global width

	path1 = sys.argv[1]
	path2 = sys.argv[2]
	name1 = os.path.join(os.path.basename(os.path.dirname(path1)), os.path.basename(path1))
	name2 = os.path.join(os.path.basename(os.path.dirname(path2)), os.path.basename(path2))
	width = max(len(name1), len(name2), 8)

	tests = [
		(10, 10),
		(20, 10),
		(50, 10),
		(100, 10),
		(200, 10),
		(500, 10),
	]

	for size, count in tests:
		print(f"{name1:>{width}} {name2:>{width}} ({size} numbers)")
		tasks = [run(path1, path2, index, size) for index in range(count)]
		await asyncio.gather(*tasks)

if __name__ == "__main__":
	asyncio.run(main())
