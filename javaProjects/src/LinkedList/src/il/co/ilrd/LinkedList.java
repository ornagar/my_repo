/**
 * 
 */
package il.co.ilrd;

import java.util.ConcurrentModificationException;
import java.util.Iterator;


/**
 * @author Or Nagar
 *
 */
public class LinkedList<E> 
implements Iterable<E> {
	
	private volatile int modLinkedListIncrement = 0;
	private Node tail;
	private Node head; 
	
	{
		tail = new Node();
		head = new Node();
		head.next = tail;
	}
	
	public boolean isEmpty() {
		return head.next == tail;
	}
	
	public void pushFront(E data) { 
		modLinkedListIncrement += 1;
		new Node(data, head);
	}
	
	public Object popFront() {
		modLinkedListIncrement += 1; 
		Object data = head.next.data;
		head.next = head.next.next;
		return data;
	} 
	
	public ListIter begin() {
		return new ListIter(this);
	}
	
	public ListIter find(Object data) {
		ListIter iter = new ListIter();
		Node runner = head.next;
		while (runner != tail) {
			if (runner.data.equals(data)) {
				iter.current = runner;
				break;
			}
			runner = runner.next; 
		}
		return iter;
	}
	
	private class Node {
		private Node next;
		private E data;
		
		private Node() {
			data = null;
			next = null;
		}
		
		public Node(E data, Node head) {
			this.data = data;
			this.next = head.next;
			head.next = this; 
		} 
	}
	
	public class ListIter implements Iterator<E> {
		private Node current;
		private volatile int iterCheckNum = modLinkedListIncrement;
		
		public ListIter() {
			current = head;
		}
		
		public ListIter(LinkedList<E> list) {
			current = list.head;
		}
		
		public ListIter(ListIter other) {
			current = other.current;
		}
		
		public E getData() {
			return current.data; 
		}

		@Override
		public boolean hasNext() {
			return current.next.next != null;
		}

		@Override
		public E next() {
			if (iterCheckNum != modLinkedListIncrement) {
				throw new ConcurrentModificationException();
			}
			current = current.next;
			return current.data;  
		}
	}

	@Override
	public Iterator<E> iterator() {
		return new ListIter(this);
	}
}
