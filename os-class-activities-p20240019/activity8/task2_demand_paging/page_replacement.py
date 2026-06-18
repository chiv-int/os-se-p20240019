from collections import deque, OrderedDict

def fifo(refs, n_frames, label=""):
    frames, queue, faults = [], deque(), 0
    print(f"\n=== FIFO — {label} (frames={n_frames}) ===")
    for ref in refs:
        if ref in frames:
            status = "HIT  "
        else:
            faults += 1
            status = "FAULT"
            if len(frames) < n_frames:
                frames.append(ref)
                queue.append(ref)
            else:
                victim = queue.popleft()
                frames[frames.index(victim)] = ref
                queue.append(ref)
        display = list(frames) + ['_'] * (n_frames - len(frames))
        print(f"  Ref {ref} | {status} | frames: {display}")
    print(f"  Total page faults (FIFO): {faults}")
    return faults

def lru(refs, n_frames, label=""):
    order = OrderedDict()
    faults = 0
    print(f"\n=== LRU  — {label} (frames={n_frames}) ===")
    for ref in refs:
        if ref in order:
            status = "HIT  "
            order.move_to_end(ref)
        else:
            faults += 1
            status = "FAULT"
            if len(order) >= n_frames:
                order.popitem(last=False)
            order[ref] = 1
        display = list(order.keys()) + ['_'] * (n_frames - len(order))
        print(f"  Ref {ref} | {status} | frames: {display}")
    print(f"  Total page faults (LRU): {faults}")
    return faults

full_string = [7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1]
my_string   = [2,0,1,2,0,3,0,4,2,3,0,3]

print("=" * 55)
print("FULL LECTURE STRING  (20 refs, 3 frames)")
print("=" * 55)
ff = fifo(full_string, 3, "full string")
fl = lru(full_string,  3, "full string")
print(f"\n  >> Full string:  FIFO faults={ff}  |  LRU faults={fl}")

print("\n" + "=" * 55)
print("MY A2 STRING  (12 refs, 3 frames)")
print("=" * 55)
mf = fifo(my_string, 3, "my A2 string")
ml = lru(my_string,  3, "my A2 string")
print(f"\n  >> My A2 string: FIFO faults={mf}  |  LRU faults={ml}")
