import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.junit.Test;

public class Box_vs_Int_Stream {
	private static final int LIST_LEN = 10_000_000;

	private class ValueObject {
		private int intMember;

		ValueObject(int intMember) {
			this.intMember = intMember;
		}

		public int getIntMember() {
			return intMember;
		}
	}

	@Test
	public void intStreamTest() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		int result = input.stream().mapToInt(ValueObject::getIntMember).sum();
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result);
		System.out.printf("intStreamTest Time:%d\n", after - before);
	}

	@Test
	public void boxingStreamTest() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		int result = input.stream().map(ValueObject::getIntMember).reduce(0, (a, b) -> a + b);
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result);
		System.out.printf("boxingStreamTest Time:%d\n", after - before);
	}

	@Test
	public void intParallelStreamTest() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		int result = input.parallelStream().mapToInt(ValueObject::getIntMember).sum();
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result);
		System.out.printf("intParallelStreamTest Time:%d\n", after - before);
	}

	@Test
	public void boxingParallelStreamTest() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		int result = input.parallelStream().map(ValueObject::getIntMember).reduce(0,
				(a, b) -> a + b);
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result);
		System.out.printf("boxingParallelStreamTest Time:%d\n", after - before);
	}
	
	@Test
	public void boxingParallelStreamReduce2Test() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		Optional<Integer> result = input.parallelStream().map(ValueObject::getIntMember).reduce((a, b) -> a + b);
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result.get());
		System.out.printf("boxingParallelStreamReduce2Test Time:%d\n", after - before);
	}
	
	@Test
	public void boxinStreamReduce2Test() {
		List<ValueObject> input = genData(LIST_LEN);
		long before = Instant.now().toEpochMilli();
		Optional<Integer> result = input.stream().map(ValueObject::getIntMember).reduce((a, b) -> a + b);
		long after = Instant.now().toEpochMilli();
		System.out.printf("Result:%d\n", result.get());
		System.out.printf("boxinStreamReduce2Test Time:%d\n", after - before);
	}

	private List<ValueObject> genData(int count) {
		List<ValueObject> ret = new ArrayList<>(count);

		for (int i = 0; i < count; ++i) {
			int n = 2;
			ValueObject vo = new ValueObject(n);
			ret.add(vo);
		}
		return ret;
	}
}
