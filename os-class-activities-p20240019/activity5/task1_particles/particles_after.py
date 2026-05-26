import threading
import time
import random

BUFFER_CAPACITY = 100
PAIR_CAPACITY = BUFFER_CAPACITY // 2

buffer = []
produced_count = 0
packaged_count = 0
running = True

empty_pairs = threading.Semaphore(PAIR_CAPACITY)
full_pairs = threading.Semaphore(0)
mutex = threading.Semaphore(1)

def producer(machine_id):
    global produced_count, running
    pair_id = 0
    while running:
        pair_id += 1
        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"
        time.sleep(random.uniform(0.02, 0.08))
        empty_pairs.acquire()
        mutex.acquire()
        if len(buffer) + 2 > BUFFER_CAPACITY:
            print("The producing machine is broken")
            running = False
            mutex.release()
            break
        buffer.append(p1)
        buffer.append(p2)
        produced_count += 1
        mutex.release()
        full_pairs.release()

def consumer():
    global packaged_count, running
    while running:
        full_pairs.acquire()
        mutex.acquire()
        if len(buffer) < 2:
            print("The packaging machine is broken")
            running = False
            mutex.release()
            break
        p1 = buffer.pop(0)
        p2 = buffer.pop(0)
        id1 = p1.rsplit("-P", 1)[0]
        id2 = p2.rsplit("-P", 1)[0]
        if id1 != id2:
            print(f"Pairs are incorrect: {p1} + {p2}")
            running = False
            mutex.release()
            break
        packaged_count += 1
        print(f"Produced pairs: {produced_count} | Packaged pairs: {packaged_count} | Buffer particles: {len(buffer)}")
        mutex.release()
        empty_pairs.release()
        time.sleep(random.uniform(0.03, 0.07))

threads = []
for i in range(1, 4):
    t = threading.Thread(target=producer, args=(i,))
    t.daemon = True
    threads.append(t)

c = threading.Thread(target=consumer)
c.daemon = True
threads.append(c)

for t in threads:
    t.start()

try:
    while running:
        time.sleep(0.1)
except KeyboardInterrupt:
    print("\nStopped.")
