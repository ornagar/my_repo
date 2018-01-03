/**
 * 
 */
package il.co.ilrd;

import static org.junit.Assert.*;

import org.junit.Test;

/**
 * @author xyz
 *
 */
public class TestComplex {

	@Test
	public void test1() {
		Complex c1 = new Complex(2, 4);
		Complex c2 = new Complex(2, 4); 
		assertTrue(c1.equals(c2));
		assertTrue(c1.hashCode() == c2.hashCode());
		
		Complex c3 = c1.add(c2);
		assertTrue(c3.equals(c1));
		
	}
	
	@Test
	public void test2() {
		Complex c1 = new Complex(2, 4);
		Complex c2 = new Complex(2, 5);
		assertTrue(!c1.equals(c2));
		assertTrue(c1.hashCode() != c2.hashCode());
		
		
	}
	
	@Test
	public void test3() {
		Complex c1 = new Complex();
		Complex c2 = new Complex();
		assertTrue(c1.equals(c2));
		assertTrue(c1.hashCode() == c2.hashCode());
		
		Complex c3 = c1.add(c2);
		assertTrue(c3.equals(c2)); 
		
	}
	
	@Test
	public void test4() {
		Shape s = new Circle();
		assertTrue(s.getColor() == "green"); 
	}
	
	@Test 
	public void test5() {
		Complex c = new Complex(2.4, 14); 
		System.out.println(c);
		assertTrue(c.getImag() < 14.0000001 && c.getImag() > 13.9999999);
		assertTrue(c.getReal() < 2.40000001 && c.getReal() > 2.399999);
	}
}
