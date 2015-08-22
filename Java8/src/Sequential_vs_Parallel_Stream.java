import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import org.junit.Test;

public class Sequential_vs_Parallel_Stream {

	private static final int LIST_LEN = 10_000_000;

	@Test
	public void stream_fullCollection() {
		List<Integer> input = genData(LIST_LEN, 2);

		long before = Instant.now().toEpochMilli();

		Stream<Integer> stream = input.stream().filter((Integer i) -> Math.sqrt(i) > i / 2);

		long after = Instant.now().toEpochMilli();
		System.out.printf("stream_fullCollection filter Time:%d\n", after - before);

		List<Integer> result = stream.collect(Collectors.toList());

		System.out.printf("stream_fullCollection collection Time:%d\n",
				Instant.now().toEpochMilli() - after);
		System.out.printf("Result count:%d\n", result.size());
	}

	@Test
	public void parallelStream_fullCollection() {
		List<Integer> input = genData(LIST_LEN, 2);

		long before = Instant.now().toEpochMilli();

		Stream<Integer> stream = input.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2);

		long after = Instant.now().toEpochMilli();
		System.out.printf("parallelStream_fullCollection filter Time:%d\n", after - before);

		List<Integer> result = stream.collect(Collectors.toList());

		System.out.printf("parallelStream_fullCollection collection Time:%d\n",
				Instant.now().toEpochMilli() - after);
		System.out.printf("Result count:%d\n", result.size());
	}

	@Test
	public void stream_noCollection() {
		List<Integer> input = genData(LIST_LEN, 0);

		long before = Instant.now().toEpochMilli();

		Stream<Integer> stream = input.stream().filter((Integer i) -> Math.sqrt(i) > i / 2);

		long after = Instant.now().toEpochMilli();
		System.out.printf("stream_noCollection filter Time:%d\n", after - before);

		List<Integer> result = stream.collect(Collectors.toList());

		System.out.printf("stream_noCollection collection Time:%d\n",
				Instant.now().toEpochMilli() - after);
		System.out.printf("Result count:%d\n", result.size());
	}

	@Test
	public void parallelStream_noCollection() {
		List<Integer> input = genData(LIST_LEN, 0);

		long before = Instant.now().toEpochMilli();

		Stream<Integer> stream = input.parallelStream().filter((Integer i) -> Math.sqrt(i) > i / 2);

		long after = Instant.now().toEpochMilli();
		System.out.printf("parallelStream_noCollection filter Time:%d\n", after - before);

		List<Integer> result = stream.collect(Collectors.toList());

		System.out.printf("parallelStream_noCollection collection Time:%d\n",
				Instant.now().toEpochMilli() - after);
		System.out.printf("Result count:%d\n", result.size());
	}

	private List<Integer> genData(int count, int number) {
		List<Integer> ret = new ArrayList<>(count);
		for (int i = 0; i < count; ++i) {
			ret.add(number);
		}
		return ret;
	}

}
