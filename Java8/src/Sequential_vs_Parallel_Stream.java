import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import org.junit.Test;

public class Sequential_vs_Parallel_Stream {

	private static final int LIST_LEN = 10000000;

	@Test
	public void sequentialStreamTest() {
		List<Integer> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		List<Integer> result = input.stream().filter((Integer i) -> Math.sqrt(i) > i / 2)
				.collect(Collectors.toList());
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result count:%d\n", result.size());
		System.out.printf("Time:%d\n", after - before);
	}

	@Test
	public void parallelStreamTest() {
		List<Integer> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		List<Integer> result = input.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2)
				.collect(Collectors.toList());
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result count:%d\n", result.size());
		System.out.printf("Time:%d\n", after - before);
	}

	private List<Integer> genData(int count) {
		List<Integer> ret = new ArrayList<>(count);
		for (int i = 0; i < count; ++i) {
			ret.add((int) (Math.random() * 20000000));
		}
		return ret;
	}

}
