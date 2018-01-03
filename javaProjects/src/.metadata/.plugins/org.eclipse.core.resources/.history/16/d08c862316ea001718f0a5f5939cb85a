package il.co.ilrd;

public class Singleton2 {
	private static Singleton2 instance = null;
	
	public static Singleton2 getInstance() {
		if (instance == null) {
				instance = new Singleton2();
		}
		return instance; 
	} 
		
	
	static public void foo2() { 
		System.out.println("inside foo2()");  
	}
	 
	private Singleton2() { System.out.println("inside ctor2");}
}
