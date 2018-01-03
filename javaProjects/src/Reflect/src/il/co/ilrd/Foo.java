package il.co.ilrd;

public class Foo {
	public void func1() {
		System.out.println("Foo.func1();");
	}
	
	public void func2() {
		System.out.println("Foo.func2();");
	}
	
	public void func3() {
		System.out.println("Foo.func3();");
	}
	
	public void func4() {
		System.out.println("Foo.func4();");
	}
	
	@Override
	public String toString() {
		return "Foo Class";
	}
	
	public class InnerFoo {
		public void func1() {
			System.out.println("InnerFoo.func1();");
		}
	
		public void func2() {
			System.out.println("InnerFoo.func2();");
		}
	
		public void func3() {
			System.out.println("InnerFoo.func3();");
		}
	
		public void func4() {
			System.out.println("InnerFoo.func4();");
		}
	
		@Override
		public String toString() {
			return "InnerFoo Class";
		}
	}
}
