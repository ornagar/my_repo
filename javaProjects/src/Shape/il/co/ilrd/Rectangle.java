package il.co.ilrd;

public class Rectangle extends Shape {
	private double width;
	private double length;
	
	public Rectangle() {
		super();
		width = length = 1.0;
	}
	
	public Rectangle(double width, double length) {
		super();
		this.width = width;
		this.length = length;
	}
	
	public Rectangle(double width, double length, String color, boolean filled) {
		super(color, filled);
		this.width = width;
		this.length = length;
	}
	
	public void setWidth(double width) {
		this.width = width;
	}
	
	public double getWidth() {
		return width;
	}
	
	public void setLength(double length) {
		this.length = length;
	}
	
	public double getLength() {
		return length;
	}
	
	@Override
	public double getArea() {
		return length * width;
	}
	
	@Override
	public double getPerimeter() {
		return length * 2 + width * 2;
	}
	
	@Override
	public String toString() {
		return "A Rectangle with width=" + width + " and length=" + length + ", which is a subclass of " + 
																							super.toString();
	}
}
