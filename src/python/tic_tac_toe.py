
class Board(object):
	
	def __init__(self):
		self.__new_table = "    |    |    \n____|____|____\n    |    |    \n____|____|____\n    |    |    \n    |    |    \n"
		self.__table = self.__new_table
		self.__moves = ['', '', '', '', '', '', '', '', '']
		self.__marks = ('X', 'O')
		self.__player = self.__marks[0]
		
	def __str__(self):
		return self.__table
	
	def mark_x(self, idx):
		mark = 'X'
		self.__moves[idx] = mark
		if idx == 0:
			temp = self.__table[0:2] + mark + self.__table[3:]
			self.__table = temp
		elif idx == 1:
			temp = self.__table[0:7] + mark + self.__table[8:]
			self.__table = temp
		elif idx == 2:
			temp = self.__table[0:12] + mark + self.__table[13:]
			self.__table = temp
		elif idx == 3:
			temp = self.__table[0:32] + mark + self.__table[33:]
			self.__table = temp
		elif idx == 4:
			temp = self.__table[0:37] + mark + self.__table[38:]
			self.__table = temp
		elif idx == 5:
			temp = self.__table[0:42] + mark + self.__table[43:]
			self.__table = temp
		elif idx == 6:
			temp = self.__table[0:62] + mark + self.__table[63:]
			self.__table = temp
		elif idx == 7:
			temp = self.__table[0:67] + mark + self.__table[68:]
			self.__table = temp
		elif idx == 8:
			temp = self.__table[0:72] + mark + self.__table[73:]
			self.__table = temp
			
	def mark_o(self, idx):
		mark = 'O'
		self.__moves[idx] = mark
		if idx == 0:
			temp = self.__table[0:2] + mark + self.__table[3:]
			self.__table = temp
		elif idx == 1:
			temp = self.__table[0:7] + mark + self.__table[8:]
			self.__table = temp
		elif idx == 2:
			temp = self.__table[0:12] + mark + self.__table[13:]
			self.__table = temp
		elif idx == 3:
			temp = self.__table[0:32] + mark + self.__table[33:]
			self.__table = temp
		elif idx == 4:
			temp = self.__table[0:37] + mark + self.__table[38:]
			self.__table = temp
		elif idx == 5:
			temp = self.__table[0:42] + mark + self.__table[43:]
			self.__table = temp
		elif idx == 6:
			temp = self.__table[0:62] + mark + self.__table[63:]
			self.__table = temp
		elif idx == 7:
			temp = self.__table[0:67] + mark + self.__table[68:]
			self.__table = temp
		elif idx == 8:
			temp = self.__table[0:72] + mark + self.__table[73:]
			self.__table = temp
	
	def check_victory(self, player):
		if self.__moves[0] == player and self.__moves[1] == player and self.__moves[2] == player:
			return True
		if self.__moves[3] == player and self.__moves[4] == player and self.__moves[5] == player:
			return True
		if self.__moves[6] == player and self.__moves[7] == player and self.__moves[8] == player:
			return True
		if self.__moves[0] == player and self.__moves[3] == player and self.__moves[6] == player:
			return True	
		if self.__moves[1] == player and self.__moves[4] == player and self.__moves[7] == player:
			return True
		if self.__moves[2] == player and self.__moves[5] == player and self.__moves[8] == player:
			return True
		if self.__moves[0] == player and self.__moves[4] == player and self.__moves[8] == player:
			return True
		if self.__moves[2] == player and self.__moves[4] == player and self.__moves[6] == player:
			return True	
		return False
		
	def resume(self):
		inp = raw_input("do you want to continue? Y/n")
		if inp == 'n':
			print "bye bye"
			return False
		else:
			print "New game!!"
			print
			return True
				
	def play(self):
		while True:
			print self.__table
			inp = int(raw_input("enter index between 1-9: "))
			if self.__moves[inp - 1] != '':
				print "error!, index taken choose a free one"
				continue
			if self.__player == self.__marks[0]:
				self.mark_x(inp-1)
			else:
				self.mark_o(inp-1)
			count_free = 0
			for i in self.__moves:
				if i == '':
					count_free += 1
			if count_free == 0:
				print "game over, its a tie"
				print self.__table
				if self.resume() == True:
					self.__table = self.__new_table
					continue
				break
			if self.check_victory(self.__player) == True:
				print "Game Over, player " + self.__player + "  won!"
				print self.__table
				if self.resume() == True:
					self.__init__()
					continue
				break
			else:
				if self.__player == self.__marks[0]:
					self.__player = self.__marks[1]
				else:
					self.__player = self.__marks[0]
b = Board()
b.play()
