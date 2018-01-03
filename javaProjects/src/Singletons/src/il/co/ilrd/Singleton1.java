package il.co.ilrd;
/**
 * 
 * @author Or Nagar
 * Eager singleton!
 *
 */
public class Singleton1 {
	private static Singleton1 instance = new Singleton1();
	
	public static Singleton1 getInstance() {
		return instance;
	}
	
	public static void foo1() { 
		System.out.println("inside foo1()"); 
	}
	
	
	
	private Singleton1() { System.out.println("inside ctor1");}
}
