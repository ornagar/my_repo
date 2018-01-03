package il.co.ilrd;

public class TestFS {
	public static void main(String[] args) {
		Entry root = Entry.buildTree(args[0]);
		root.printTree();

	}
}
