package il.co.ilrd;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class TestShape {

	@Test
	void test() {
		Shape s = new Circle();
		assertTrue(s.getArea() == 1.0 * 1.0 * java.lang.Math.PI);
	}

}
