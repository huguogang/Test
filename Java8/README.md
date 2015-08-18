# Test of Java 8 features

## sequentialStreamTest vs. parallelStreamTest

This pair of test is showing a simple switch from `stream` to `parallelStream` can easily gain some performance for the filtering. On my laptop (4 core CPU), it is consistently showing close to 4 times improvements (~130 ms vs. ~40 ms);