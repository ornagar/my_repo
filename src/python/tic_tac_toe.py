def AIcheck(self):
		#Offense should come before defense so that the AI will try to win if possible
		#This is built on the self.check function
		self.ttt=[[row[i] for row in self.TTT] for i in range(3)]
		#OFFENSE
		#this is the vertical checklist    
		for h in range(0,3):
			k=0
			j=0
			if sum(self.TTT[h])==18:
				while k <3:
					if k==h:
						while j <3:
							if self.trigger==False:
								if self.TTT[k][j]==0:
									self.cross(j,k)
									break
							j+=1
					k+=1
		#this is the horizontal checklist    
		for h in range(0,3):
			k=0
			j=0
			if sum(self.ttt[h])==18:                        
				while k <3:
					if k==h:
						while j <3:
							if self.trigger==False:
								if self.ttt[k][j]==0:
									self.cross(k,j)
									break
							j+=1
					k+=1
		#this is the diagonal checklist    
		if self.TTT[1][1]==9:
			if self.TTT[0][0]==9:
				if self.trigger==False:
					if self.TTT[2][2]==0:
						self.cross(2,2)
			if self.TTT[0][2]==9:
				if self.trigger==False:
					if self.TTT[2][0]==0:
						self.cross(0,2)
			if self.TTT[2][0]==9:
				if self.trigger==False:
					if self.TTT[0][2]==0:
						self.cross(2,0)
			if self.TTT[2][2]==9:
				if self.trigger==False:
					if self.TTT[0][0]==0:
						self.cross(0,0)
		#DEFENSE
		#this is the horizontal checklist    
		for h in range(0,3): 
			k=0
			j=0            
			if sum(self.TTT[h])==2:
				while k <3:
					if k==h:
						while j <3:
							if self.trigger==False:
								if self.TTT[k][j]==0:
									self.cross(j,k)
									break
							j+=1
					k+=1
		#this is the vertical checklist
		for h in range(0,3):
			k=0
			j=0
			if sum(self.ttt[h])==2:                        
				while k <3:
					if k==h:
						while j <3:
							if self.trigger==False:
								if self.ttt[k][j]==0:
									self.cross(k,j)
									break
							j+=1
					k+=1                    
		#this is the diagonal checklist
		if self.TTT[1][1]==1:
			if self.TTT[0][0]==1:
				if self.trigger==False:
					if self.TTT[2][2]==0:
						self.cross(2,2)
			if self.TTT[0][2]==1:
				if self.trigger==False:
					if self.TTT[2][0]==0:
						self.cross(0,2)
			if self.TTT[2][0]==1:
				if self.trigger==False:
					if self.TTT[0][2]==0:
						self.cross(2,0)
			if self.TTT[2][2]==1:
				if self.trigger==False:
					if self.TTT[0][0]==0:
						self.cross(0,0)
		#NEUTRAL
		if self.TTT[1][1]==0:
			if self.trigger==False:
				self.cross(1,1)
				self.trigger=True
		else:
			if self.trigger==False:
				self.randmove()
