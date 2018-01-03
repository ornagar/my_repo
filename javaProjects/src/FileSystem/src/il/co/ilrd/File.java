package il.co.ilrd;

public class File extends Entry {
	
	public File(String name) {
		super(name);
	}
	
	public String getName() {
		return super.getName();
	}
	
	@Override
	public void print(String pre) {
		System.out.println(pre + name);
	}

}
