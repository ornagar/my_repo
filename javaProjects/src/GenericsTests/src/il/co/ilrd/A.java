package il.co.ilrd;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class A {
	public static void main(String[] args) {
		List rawList = new ArrayList();
		List<?> listOfAnyType;
		List<Object> listOfObject = new ArrayList<Object>();
		List<String> listOfString = new ArrayList<String>();
		List<Integer> listOfInteger = new ArrayList<Integer>();
		
		rawList.add(1);
		rawList.add("heel");
		System.out.println(rawList.get(0));
		System.out.println(rawList.get(1));
		
	}
}
