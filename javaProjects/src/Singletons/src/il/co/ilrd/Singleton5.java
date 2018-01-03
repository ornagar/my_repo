package il.co.ilrd;

public enum Singleton5 {
	GETINSTANCE;
	
	public static void foo5() { 
		System.out.println("inside foo5()"); 
	}
	
	public static Singleton5 getInstance() {
		return Singleton5.GETINSTANCE;
	}
}
