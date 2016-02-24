try:
    import Queue as Q  # ver. < 3.0
except ImportError:
    import queue as Q

q = Q.PriorityQueue()
q.put(10)
q.put(1)
q.put(5)
while not q.empty():
	print q.get(),
