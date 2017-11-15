class Counter(object):
	number = 0
	
	def __init__(self):
		type(self).number += 1
		
	def __del__(self):
		type(self).number -= 1

class Account(Counter):
	def __init__(self, holder, balance, credit_line = 1500):
		Counter.__init__(self)
		self.__Holder = holder
		self.__Number = self.number
		self.__Balance = balance
		self.__CreditLine = credit_line
	
	def deposit(self, amount):
		self.__Balance += amount
		
	def withdraw(self, amount):
		if self.__Balance - amount < -self.CreditLine:
			return False
		else:
			self.__Balance -= amount
			return True
			
	def balance(self):
		return self.__Balance
		
	def transfer(self, target, amount):
		if self.__Balance - amount < -self.CreditLine:
			return False
		else:
			self.__Balance -= amount
			target.__Balance += amount
			return True
			
			
if __name__ == '__main__':
	my_account = Account("Or Nagar", 0)
	my_account.deposit(123.45)
	print my_account.balance()
	print my_account._Account__Number
	del my_account
	my_account2 = Account("Or Nagar", 0)
	my_account2.deposit(123.45)
	print my_account2.balance()
	print my_account2._Account__Number

