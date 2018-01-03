package il.co.ilrd;

import static org.junit.jupiter.api.Assertions.*;


import org.junit.jupiter.api.Test;

class TestLinkedList {

	@Test
	void testList1() {
		LinkedList<Integer> list1 = new LinkedList<>();
		
		for (int i = 0; i < 50; ++i) {  
			list1.pushFront(i); 
		} 
		
		LinkedList<String> list2 = new LinkedList<>();
		
		for (int i = 0; i < 50; ++i) {
			list2.pushFront(Integer.toString(i));
		}
		
		LinkedList<Integer> list3 = new LinkedList<>();
		
		for (int i = 0; i < 50; ++i) {   
			list3.pushFront(i); 
		}

		LinkedList<Integer>.ListIter iter1 = list1.find(40);
		LinkedList<Integer>.ListIter iter3 = list3.find(40);
		LinkedList<String>.ListIter iter2 = list2.find("40");  
 
		assertTrue(iter2.getData().equals("40"));
		assertTrue(iter1.getData().equals(40));  
		assertTrue(iter3.getData().equals(40)); 

		for (Integer i : list1) {
			System.out.println(i); 
		} 
	} 

}
