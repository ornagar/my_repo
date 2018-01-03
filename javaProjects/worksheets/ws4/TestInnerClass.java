//package innerclasses;
/**
 * Test InnerClass is the main class here
 */
public class TestInnerClass {
	/**
	 * main method.
	 */
	public static void main(String[] args) {
		OuterClass st = new OuterClass();
		OuterClass.InnerClass f1 = st.new InnerClass();
		f1.foo2(23);
	}
}

class OuterClass {
	public int x = 0;
	public void foo1() {
		System.out.println("running foo1() ");
	}
	class InnerClass {
		public int x = 1;
		void foo2(int x) {
			foo1();
			System.out.println("x = " + x);
			System.out.println("this.x = " + this.x);
			System.out.println("OuterClass.this.x = " + OuterClass.this.x);
			
			OuterClass c = new OuterClass() {
				public void foo1() {
					System.out.println("running foo3() from anonymous class");
				}
			};
			
			c.foo1();
		}
	}
}

