# Test of Java 8 features

## Sequential_vs_Parallel_Stream

`.stream().filter((Integer i) -> Math.sqrt(i) > i / 2).collect(Collectors.toList())`
`.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2).collect(Collectors.toList())`

            |Collect Nothing |Collect 10,000,000
 -----------|---------------:|------------------:
 Stream     |70              |330
 Parallel   |25              |1000

Observations:
* Parallel filtering is an easy win, performance gained about 3 times on a quad-core computer
* Parallel collection is big **loser**, the `collect` part took about 3 times longer


## Box_vs_Int_Stream
`mapInt().sum()`
`map().reduce(0, (a, b) -> a + b)`

            |Boxing |Int
 -----------|------:|----:
 Stream     |115    |85
 Parallel   |210    |87
 
Observations:
* Parallel streaming does not improve performance for this algorithm, if not worse;
* Boxing does have non-trivial overhead vs. IntStream; 