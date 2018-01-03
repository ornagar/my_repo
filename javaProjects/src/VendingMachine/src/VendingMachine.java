public class VendingMachine {
	
	volatile private State state = State.DISCONNECTED;
	private int coins = 0;
	Thread thread;
	
	private void connect() { 
		state.connect(this);
		System.out.println("Current state is: " + state + '\n');
	} 
	
	public void insertCoin(int coin) {
		state.insertCoin(this, coin);
		System.out.println("Current state is: " + state + '\n');
	}
	
	public void chooseDrink(Drink drink) {
		state.chooseDrink(this, drink); 
		System.out.println("Current state is: " + state + '\n');
	}
	
	private void timeOut() {
		state.timeOut(this);
	}
	
	public void stop() throws InterruptedException {
		thread.interrupt();
		thread.join();
	}
	
	public void run() {
		System.out.println("Current state is: " + state + "\nPlease wait a few seconds.");
		thread = new Thread() {
			@Override
			public void run() {
					try { 
						while(true) {
							Thread.sleep(2000);
							timeOut(); 
						}
					} catch (InterruptedException e) {
						System.out.println("Timer thread is exiting.");
					}
			}
		};
		
		thread.start();
	}
	
	static private enum State { 
		DISCONNECTED {
			@Override
			void connect(VendingMachine v) {
				System.out.println("Connecting...");
				System.out.println("Loading system...");
				System.out.println("Testing sensores...");
				System.out.println("Loading Completed...");
				System.out.println("Connected!!");
				v.state = IDLE;
			}
			
			@Override 
			void timeOut(VendingMachine v) {
				v.connect();
			}
		}, 
		IDLE {
			
			@Override
			void insertCoin(VendingMachine v, int coin) {
				v.coins += coin;
				System.out.println("Total of: " + v.coins + "$ inserted");
				v.state = HAS_COINS;
			}	
			
			@Override
			void chooseDrink(VendingMachine v, Drink drink) {
				System.out.println(drink + " drink costs " + drink.getPrice());
			}
		},
		HAS_COINS {
			 
			@Override
			void insertCoin(VendingMachine v, int coin) {
				v.coins += coin;
				System.out.println("Total of: " + v.coins + "$ inserted");
			}
			
			@Override
			void chooseDrink(VendingMachine v, Drink drink) {
				int price = drink.getPrice();
				if (v.coins >= price) {
					System.out.println("Your change is: " + (v.coins - price) + "$");
					System.out.println("Returning coins...");
					v.coins = 0;
					v.state = DELIVERING;
				} else {
					System.out.println("Missing " + (price - v.coins) + "$");
				}
			}
		},
		DELIVERING {
					
			@Override
			void timeOut(VendingMachine v) {
				System.out.println("Delivering drink"); 
				System.out.println("Completing transaction");
				v.state = TRANSACTION_COMPLETE;
			}
		},
		TRANSACTION_COMPLETE {
			
			@Override
			void timeOut(VendingMachine v) {
				System.out.println("Returning to idle state");
				System.out.println("To buy a drink please insert some coins...");
				v.state = IDLE;
			}
		}; 
		
		void connect(VendingMachine v) { System.out.println("!!!!!!Wrong choise!!!!!!!"); }
		void insertCoin(VendingMachine v, int coin) { System.out.println("!!!!!!Wrong choise!!!!!!!\nTake your money back"); }
		void chooseDrink(VendingMachine v, Drink drink) { System.out.println("!!!!!!Wrong choise!!!!!!!"); }
		void timeOut(VendingMachine v) { }
	}
	
	public enum Drink {
		COKA_COLA(5) ,
		COKA_COLA_ZERO(6) ,
		SPRITE(5),
		FANTA(6); 

		private final int price;
		
		Drink(int price) {
			this.price = price;
		}
		
		private int getPrice() {
			return price;
		}
	}
}
 