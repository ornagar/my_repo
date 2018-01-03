package il.co.ilrd;

public class Square extends Rectangle {
	public Square() {
		super(1, 1);
	}
	
	public Square(double side) {
		super(side, side);
	}
	
	public Square(double side, String color, boolean filled) {
		super(side, side, color, filled);
	}
	
	public void setSide(double side) {
		super.setLength(side);
		super.setWidth(side);
	}
	
	public double getSide() {
		return super.getLength();
	}
	
	@Override
	public void setWidth(double width) {
		super.setLength(width);
		super.setWidth(width);
	}
	
	@Override
	public void setLength(double length) {
		super.setLength(length);
		super.setWidth(length);
	}
	
	@Override
	public String toString() {
		return "A Square which is a subclass of " + super.toString();
	}
}
