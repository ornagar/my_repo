import java.util.ArrayList;
import java.lang.Runtime;
class MyTest {
	public static void main(String[] args) {
		while (true) {
			ArrayList<String> elements[] = new ArrayList[1000];
	
			for (int i = 0; i < 1000; i++) {
				elements[i] = new ArrayList(1000);
				System.out.print(java.lang.Runtime.getRuntime().freeMemory());
				System.out.print(" - ");
			}
		}
	}
}
