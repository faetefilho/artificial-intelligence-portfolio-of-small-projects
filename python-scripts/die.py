from random import randint

class Die:
	"""class to create a dice and row it"""

	def __init__(self,num_sides=6):
		"""create dice with n sides"""
		self.num_sides=num_sides

	def roll(self):
		return randint(1,self.num_sides)
