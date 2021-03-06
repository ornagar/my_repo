package il.co.ilrd;

public class Singleton4 {
	
	private static class Inner {
		private static Singleton4 instance = new Singleton4();
	}
	
	public static Singleton4 getInstance() { 
		return Inner.instance;
	}
	
	static public void foo4() { 
		System.out.println("inside foo4()");  
	}
	
	private Singleton4() { System.out.println("inside ctor4");} 
}
