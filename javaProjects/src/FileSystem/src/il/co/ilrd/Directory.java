package il.co.ilrd;

import java.util.Vector;

public class Directory extends Entry {
	private Vector<Entry> entries;
	
	public Directory(String path) {
		super(path);
		entries = new Vector<>();
	}
	
	public Directory lastDir() {
		return (Directory)entries.get(0);
	}
	
	public void addEntry(Entry en) {
		entries.add(en);
	}
	
	@Override
	public void print(String pre) {
		System.out.println(pre + name);
		for (Entry en : entries) {
			en.print("│   " + pre);
		}
		
	}
}
