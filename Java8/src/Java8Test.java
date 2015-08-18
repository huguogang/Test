import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import org.junit.Test;

/**
 * Some tests of new language features in Java 8.
 * 
 * @author huguogang
 */
public class Java8Test {

	private static final int LIST_LEN = 10000000;

	@Test
	public void sequentialStreamTest() {
		List<Integer> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		List<Integer> ones = input.stream().filter((Integer i) -> Math.sqrt(i) > i / 2)
				.collect(Collectors.toList());
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result count:%d\n", ones.size());
		System.out.printf("Time:%d\n", after - before);
	}

	@Test
	public void parallelStreamTest() {
		List<Integer> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		List<Integer> ones = input.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2)
				.collect(Collectors.toList());
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result count:%d\n", ones.size());
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
