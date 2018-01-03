package il.co.ilrd;

import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.stream.Collectors;

public class CollectionsTest {

	public static void main(String[] args) {
		
		int[] intArray = {1,5,2,6,4,7,9,8,3};
		System.out.println(Arrays.toString(intArray));
		
		List<Integer> l = Arrays.stream(intArray).boxed().collect(Collectors.toList());
		Collections.sort(l);
		System.out.println(l);
		
		LinkedHashMap<String, Integer> days = new LinkedHashMap<>();
		days.put("Sunday", 1);
		days.put("Monday", 2);
		days.put("Tuesday", 3);
		days.put("Wednesday", 4);
		days.put("Thursday", 5);
		days.put("Friday", 6);
		days.put("Saturday", 7);
		
		for (Iterator<String> iter = days.keySet().iterator(); iter.hasNext();) {
			System.out.println(iter.next());
		}
		
		for (Iterator<Integer> iter = days.values().iterator(); iter.hasNext();) {
			System.out.println(iter.next());
		}
		
		
		
		DataObject[] d = {new DataObject(1), new DataObject(1400), new DataObject(1321), new DataObject(5), new DataObject(2)};
		LinkedHashMap<String, Integer> calc = new LinkedHashMap<>();
		
		for (DataObject i : d) {
			Integer sum = calc.get(i.code);
			calc.put(i.code, sum == null ? 1 : sum + i.value);
		}
		System.out.println(calc);
	} 

}
