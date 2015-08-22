# Test of Java 8 features

## Sequential_vs_Parallel_Stream

`.stream().filter((Integer i) -> Math.sqrt(i) > i / 2).collect(Collectors.toList())`
`.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2).collect(Collectors.toList())`

            |Collect Nothing |Collect 10,000,000
 -----------|---------------:|------------------:
 Stream     |70              |330
 Parallel   |25              |1000

Observations:
* Parallel filtering is an easy win, performance gained about 3 times on a quad-core computer;
* Parallel collection is big **loser**, the `collect` part took about 3 times longer;
* Parallel streaming performance has very high variation;


## Box_vs_Int_Stream
Int        		`mapInt().sum()`
Boxing     		`map().reduce(0, (a, b) -> a + b)`
Boxing Reduce 2	`map().reduce((a, b) -> a + b)`

            |Boxing |Int  | Boxing Reduce 2
 -----------|------:|----:|-----------------:
 Stream     |115    |80   |108
 Parallel   |64     |40   |110
 
Observations:
* Parallel streaming does not improve performance for this algorithm, if not worse;
* Boxing does have non-trivial overhead vs. IntStream; 
* Parallel stream again showed very high variability. It actually rarely achieves the numbers shown above;