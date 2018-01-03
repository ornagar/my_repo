import java.lang.reflect.Type;
import java.lang.reflect.Modifier;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class ObjectAnalyzer {
	public Class<?> cls;
	public Class<?> inner;
	
	public ObjectAnalyzer(String className) throws ClassNotFoundException {
		cls = Class.forName(className);
	}
	
	public ObjectAnalyzer(String className, String inner) throws ClassNotFoundException {
		cls = Class.forName(className);
		
		this.inner = Class.forName(inner);
	}
	
	public void printAncestor() {
		System.out.println("\nSuperclass:");
		Class<?> intf = cls.getSuperclass();

		System.out.println(intf);

	}
	
	public void printInterfaces() {
		System.out.println("\nInerfaces:");
		Type[] intfs = cls.getGenericInterfaces();
		for (Type intf : intfs) {
			System.out.println(intf.toString());
		}
	}
	
	public void printModifiers() {
		System.out.println("\nModifiers:");
		System.out.println(Modifier.toString(cls.getModifiers()));
	}
	
	public void printMembers() {
		System.out.println("\nMembers:");
		Constructor<?>[] ctors = cls.getConstructors();
		Field[] fields = cls.getFields();
		Method[] methods = cls.getMethods();
		
		System.out.println("\nCtors:");
		for (Constructor<?> ctor : ctors) {
			System.out.println(ctor.toGenericString());
		}
		
		System.out.println("\nFields:");
		for (Field fld : fields) {
			System.out.println(fld.toGenericString());
		}
		
		System.out.println("\nMethods:");
		for (Method mthd : methods) {
			System.out.println(mthd.toGenericString());
		}
	}
	
	public Object newInstance() {
		
  	 	Object obj = null;
  	 	
  	 	try {
  	 		obj = cls.newInstance();
  	 	} catch (Exception ex) {
  	 		
  	 	}
  	 	
  	 	return obj;
	}
	
	public Object newInnerInstance(Object outer) {
		
  	 	Object innerObj = null;
  	 	Constructor<?> ctor = null;
  	 	try {
	  	 	ctor = inner.getDeclaredConstructor(cls);
  	 		innerObj = ctor.newInstance(outer);
  	 	} catch (Exception ex) {
  	 		System.out.println("new Instance failure");
  	 	}
  	 	
  	 	if (innerObj == null || ctor == null) {
				System.out.println("new Instance failure");
			}
  	 	
  	 	return innerObj;
	}
	
	public Method[] getMethods() {
  	 	Method[] methods = cls.getDeclaredMethods();
  	 	return methods;
	}
	
	public Method[] getInnerMethods() {
  	 	Method[] methods = inner.getMethods();

  	 	return methods;
	}
}