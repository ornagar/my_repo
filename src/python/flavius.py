def flavius(num_of_soldiers):
	mask = num_of_soldiers
	count = 0
	while mask > 1:
		mask >>= 1
		count +=1
		
	while count > 0:
		mask <<= 1
		count -= 1
		
	soldier = ((num_of_soldiers ^ mask) << 1) | 1
	return soldier
	
	
if __name__ == "__main__":
	soldiers = int(input("type number of soldiers: "))
	winner = flavius(soldiers)
	print "and the winner is: ", winner
	
