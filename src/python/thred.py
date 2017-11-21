import subprocess
from time import time
import os
from threading import Thread, Lock
from collections import deque
from time import sleep
from queue import Queue


"""
def factorize(number):
	for i in range(1, number + 1):
		if number % i == 0:
			yield i


class FactorizeThread(Thread):
	def __init__(self, number):
		super().__init__()
		self.number = number

	def run(self):
		self.factors = list(factorize(self.number))
"""	

"""		
numbers = [2139079, 1214759, 1516637, 1852285]
start = time()
threads = []
for number in numbers:
	thread = FactorizeThread(number)
	thread.start()
	threads.append(thread)

for thread in threads:
	thread.join()
end = time()
print('Took %.3f seconds' % (end - start))
"""



"""
import select

def slow_systemcall():
	select.select([], [], [], 0.1)
	
def compute_helicopter_location(index):
	total = 0;
	for i in range(500):
		total += i
	return total

start = time()
threads = []
for _ in range(5):
	thread = Thread(target=slow_systemcall)
	thread.start()
	threads.append(thread)
	
for i in range(5):
	compute_helicopter_location(i)
for thread in threads:
	thread.join()
end = time()
print('Took %.3f seconds' % (end - start))
"""
"""
class Counter(object):
	def __init__(self):
		self.count = 0
		
	def increment(self, offset):
		self.count += offset
		

class LockingCounter(object):
	def __init__(self):
		self.lock = Lock()
		self.count = 0
		
	def increment(self, offset):
		with self.lock:
			self.count += offset

def worker(sensor_index, how_many, counter):
	for _ in range(how_many):
		#total = 0
		#for i in range(10000):
		#	total += i
		counter.increment(1)

def run_threads(func, how_many, counter):
	threads = []
	for i in range(5):
		args = (i, how_many, counter)
		thread = Thread(target=func, args=args)
		threads.append(thread)
		thread.start()
	for thread in threads:
		thread.join()
		
how_many = 10 ** 5
counter = LockingCounter()
run_threads(worker, how_many, counter)
print('Counter should be %d, found %d' % (5 * how_many, counter.count))
"""

"""
def download(item):
	return item

def resize(item):
	return item

def upload(item):
	return item

class MyQueue(object):
	def __init__(self):
		self.items = deque()
		self.lock = Lock()
		
	def put(self, item):
		with self.lock:
			self.items.append(item)
	
	def get(self):
		with self.lock:
			return self.items.popleft()
			

class Worker(Thread):
	def __init__(self, func, in_queue, out_queue):
		super().__init__()
		self.func = func
		self.in_queue = in_queue
		self.out_queue = out_queue
		self.polled_count = 0
		self.work_done = 0
		
	def run(self):
		while True:
			self.polled_count += 1
			try:
				item = self.in_queue.get()
			except IndexError:
				sleep(0.01)
			else:
				result = self.func(item)
				self.out_queue.put(result)
				self.work_done += 1
				
download_queue = MyQueue()
resize_queue = MyQueue()
upload_queue = MyQueue()
done_queue = MyQueue()
threads = [
	Worker(download, download_queue, resize_queue),
	Worker(resize, resize_queue, upload_queue),
	Worker(upload, upload_queue, done_queue),
]

for thread in threads:
	thread.start()
for _ in range(1000):
	download_queue.put(object())
	
while len(done_queue.items) < 1000:
	pass

processed = len(done_queue.items)
polled = sum(t.polled_count for t in threads)
print('Processed', processed, 'items after polling', polled, 'times')
"""
print("שלום")
