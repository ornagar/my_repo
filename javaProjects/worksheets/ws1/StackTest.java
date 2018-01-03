
public class StackTest {

	public static void main(String[] args) {
		Class s;
		if (args.length == 1) {
			System.out.println(args[0]);
			try {		
				s = java.lang.Class.forName(args[0]);	
				
				System.out.println(s.getClass().getName());
				System.out.println(s.getClass().getInterfaces()[0]);
				System.out.println(s.getClass().isInterface());
				System.out.println(s.getClass().getSuperclass());

			} catch (ClassNotFoundException ex) {
				System.out.println("Error: exception");
			}
		}else {
			System.out.println("Error no args given");
		}
		
		Day d = Day.fromValue(3);
		System.out.println(d);
		System.out.println(d.dayValue());
		
		Day.printAll();
	}
}

class Base {
	
}

class StackTest2 extends Base{

	public int m_a = 2;	

	static void over(int x) {
		System.out.println("stack number is" + x);
		if (x == 1000)
			return;
			
		over(x + 1);
	}	
}


enum Day {
	SUN {
		public int dayValue() { return 1;}
	}, 
	MON {
		public int dayValue() { return 2;}
	},
	TUR {
		public int dayValue() { return 3;}
	},
	WED {
		public int dayValue() { return 4;}
	},
	TUE {
		public int dayValue() { return 5;}
	},
	FRY {
		public int dayValue() { return 6;}
	},
	SAT {
		public int dayValue() { return 7;}
	};
	
	public abstract int dayValue();
	
	public static Day fromValue(int day) {
		switch (day) {
			case 1: return SUN;
			case 2: return MON;
			case 3: return TUR;
			case 4: return WED;
			case 5: return TUE;
			case 6: return FRY;
			case 7: return SAT;
			default: return SUN;
		}
	}
	
	public static void printAll() {
		for (Day day : Day.values()) {
			System.out.println(day);
		}
	}

}
