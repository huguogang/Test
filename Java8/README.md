# Test of Java 8 features

## Sequential_vs_Parallel_Stream

This pair of test is showing a simple switch from `stream` to `parallelStream` can easily gain some performance for the filtering. On my laptop (4 core CPU), it is consistently showing close to 4 times improvements (~130 ms vs. ~40 ms);

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