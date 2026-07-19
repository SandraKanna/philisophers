# Philosophers

A classic concurrency exercise from the 42 curriculum: N philosophers sit at a round table with one fork between each pair. To eat, a philosopher needs both adjacent forks. Each philosopher is a thread, each fork is a mutex, and the program must guarantee no data races, no deadlocks, no scrambled output, and death detection within 10 ms.

Written in C, following the 42 Norm (functions ≤ 25 lines, ≤ 5 functions per file, no globals), which explains some structural choices.

## Usage

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Time is in milliseconds. Philosophers loop: eat → sleep → think. 
A philosopher who goes longer than `time_to_die` without starting a meal dies and the simulation stops; with the optional fifth argument, it also stops once everyone has eaten that many times.

## Concurrency design

One thread per philosopher, one mutex per fork, plus three state mutexes: `meals_lock` (last meal time, meal count), `death_lock` (stop flag), `print_lock` (output serialization).

### Deadlock: the naive version

The table, with 4 philosophers — each fork (mutex) sits between two neighbors, so adjacent philosophers share it:

```
        P1
    F0      F3
 P2            P4
    F1      F2
        P3
```

"Everyone grabs their left fork first" looks like a consistent rule, but *left* is relative to each seat. Watch what happens when all four get hungry at the same instant. Step 1 — every left hand succeeds, because each one reaches for a different fork:

```
P1 holds F0     P2 holds F1     P3 holds F2     P4 holds F3
```

All four forks are now taken. Step 2 — every right hand reaches out and finds the neighbor already holding that fork:

```
P1 waits for F3  →  held by P4
P4 waits for F2  →  held by P3
P3 waits for F1  →  held by P2
P2 waits for F0  →  held by P1   ← P1 is where we started
```

The wait chain closes on itself. Reading it as "who is blocked by whom":

```
P1 ──▶ P4 ──▶ P3 ──▶ P2 ──▶ P1 ──▶ ...    (X ──▶ Y means "X waits for a fork Y holds")
```

Nobody will ever release what they hold (they release only after eating, and none can eat), so all four block forever. That closed circle is the *circular wait* — the [Coffman condition](https://faq.computersciencewiki.org/index.php/home/article/coffman-conditions)  this design fails to break.

### The fix: resource ordering

Each philosopher locks the fork at the **lower memory address** first. The forks live in one contiguous array, so address order is index order — a global order all threads agree on, regardless of seat. Re-run the same worst case (all four hungry at the same instant), now with each one reaching for its lower-numbered fork first:

```
P1: F0 then F3      P2: F0 then F1      P3: F1 then F2      P4: F2 then F3
```

Note the effect: P1 and P2 now compete for the *same first fork* (F0). The loser waits **holding nothing** — blocking nobody — and F3 stays free on the table for P1 to complete a pair. A wait chain can only move toward higher indices:

```
F0 ──▶ F1 ──▶ F2 ──▶ F3 ──▶ ∅     a cycle would need to come back down — impossible
```

Deadlock becomes impossible by construction, not by timing luck.

### Accurate death detection

A monitor loop in the main thread polls each philosopher every ~1 ms. Two details keep detection precise under tight timings: `last_meal` is updated immediately after the second fork is acquired (before any logging), so a philosopher holding both forks is never falsely declared dead; and the monitor takes `print_lock` only when actually printing a death, keeping contention low.

## Build and run

```bash
make        # builds ./philo
make re     # full rebuild
make tsan   # rebuild with ThreadSanitizer and run a race check
```

```bash
./philo 4 410 200 200       # ~10 ms of slack: nobody dies
./philo 5 800 200 200 7     # stops after everyone eats 7 times
./philo 1 800 200 200       # single philosopher: dies at ~800 ms
./philo 2 410 200 200       # 2 philos, 2 forks, strict turns: hardest timing test, nobody dies
```

Some parameter sets are mathematically unsurvivable no matter the implementation (e.g. `./philo 7 100 5 300` — sleeping 300 ms with a 100 ms death timer). The program's job there is to detect the death on time.
