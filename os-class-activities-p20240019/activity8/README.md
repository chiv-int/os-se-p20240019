# Class Activity 8 - Memory Management & Virtual Memory

- **Student Name:** ChivInthera   **Student ID:** p20240019
- **Personalization:** a = 9 , b = 1 → N = (10x9+1) mod 128 = 91
- **Programming Language Used:** python

## Part A1 — Address translation (by hand)

Personalization: a=9, b=1, N = (10×9+1) mod 128 = 91

| LA  | page = LA÷16 | offset = LA mod 16 | valid? | frame | physical = frame×16+offset |
|-----|-------------|-------------------|--------|-------|---------------------------|
| 20  | 1           | 4                 | YES    | 2     | 2×16+4 = 36               |
| 100 | 6           | 4                 | YES    | 0     | 0×16+4 = 4                |
| 48  | 3           | 0                 | NO     | —     | Page fault                |
| 16  | 1           | 0                 | YES    | 2     | 2×16+0 = 32               |
| 127 | 7           | 15                | YES    | 4     | 4×16+15 = 79              |
| 91  | 5           | 11                | NO     | —     | Page fault                |

**Q1.** The offset is the position within the page just moves to a different frame, so the position inside it is unchanged.

**Q2.** Largest offset = 15 (values 0–15), needs 4 bits (2⁴ = 16).

**Q3.** 60 + a = 60 + 9 = 69 bytes needed.
Pages = ceil(69 ÷ 16) = 5 pages allocated.
Last page uses 69 mod 16 = 5 bytes → internal fragmentation = 16 - 5 = 11 bytes wasted.

## Part A2 — Page replacement (by hand)

My reference string: 2 0 1 2 0 3 0 4 2 3 0 3
Frames: 3, start empty

Prediction: I predict FIFO will cause more faults because it may evict 
pages needed soon, while LRU keeps recently used pages.

### FIFO trace
| Ref | H/F | F1 | F2 | F3 | Evicted |
|-----|-----|----|----|----|---------|
| 2   | F   | 2  | _  | _  | —       |
| 0   | F   | 2  | 0  | _  | —       |
| 1   | F   | 2  | 0  | 1  | —       |
| 2   | H   | 2  | 0  | 1  | —       |
| 0   | H   | 2  | 0  | 1  | —       |
| 3   | F   | 3  | 0  | 1  | 2       |
| 0   | H   | 3  | 0  | 1  | —       |
| 4   | F   | 3  | 4  | 1  | 0       |
| 2   | F   | 3  | 4  | 2  | 1       |
| 3   | H   | 3  | 4  | 2  | —       |
| 0   | F   | 0  | 4  | 2  | 3       |
| 3   | F   | 0  | 3  | 2  | 4       |
Total FIFO faults: 8

### LRU trace
| Ref | H/F | F1 | F2 | F3 | Evicted |
|-----|-----|----|----|----|---------|
| 2   | F   | 2  | _  | _  | —       |
| 0   | F   | 2  | 0  | _  | —       |
| 1   | F   | 2  | 0  | 1  | —       |
| 2   | H   | 2  | 0  | 1  | —       |
| 0   | H   | 2  | 0  | 1  | —       |
| 3   | F   | 2  | 0  | 3  | 1       |
| 0   | H   | 2  | 0  | 3  | —       |
| 4   | F   | 4  | 0  | 3  | 2       |
| 2   | F   | 4  | 0  | 2  | 3       |
| 3   | F   | 4  | 3  | 2  | 0       |
| 0   | F   | 0  | 3  | 2  | 4       |
| 3   | H   | 0  | 3  | 2  | —       |
Total LRU faults: 8

Result: Both tied at 8 faults. My prediction was wrong — I thought FIFO 
to fault more, but LRU also faulted 8 times on this string.

## Part B — Simulator verification
![Translation](screenshots/task1_translation.png)
![FIFO](screenshots/task2_fifo.png)
![LRU](screenshots/task2_lru.png)
- Did the simulator match my A1 table? …
- Did the simulator's counts for my A2 string match my hand totals? … (if not, what was wrong)

## Part C — Applied reasoning
1. …  2. …  3. …  4. …  5. …