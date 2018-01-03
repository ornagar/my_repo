public class Test {
	public static void main(String[] args) {
		Useful x = new MoreUseful(2);
	}
}

class Useful {
	public int x;
	public int y;
	public static int z;
	
	{
		System.out.println("inside Useful initialization block");
		x = 14;
		y = 3;
	}
	
	public Useful(int x) {
		System.out.println("inside Useful ctor");
		this.x = x;
		this.y = x;
		
		System.out.println("exiting Useful ctor");
	}
	
	static {
		System.out.println("inside Useful static initialization block");
		z = 4;
	}
	
	public void f() {}
	public void g() {}
}
class MoreUseful extends Useful {

	public int a;
	public int b;
	public static int c;
	
	{
		System.out.println("inside MoreUseful initialization block");
		a = 14;
		b = 3;
	}
	
	public MoreUseful(int x) {
		super(x);
		System.out.println("inside MoreUseful ctor");
		this.a = x;
		this.b = x;
		System.out.println("exiting MoreUseful ctor");
	}
	
	static {
		System.out.println("inside MoreUseful static initialization block");
		c = 4;
	}
	
	public void h() {} 
	public void i() {}
	public void j() {}
	public void k() {}
}

