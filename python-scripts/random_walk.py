from random import choice

class RandomWalk:
	"""A class to gen random walks"""

	def __init__(self, num_points=5000):
		"""initialize points"""
		self.num_points=num_points

		# all walks starts at zero
		self.x_values=[0]
		self.y_values=[0]

	def fill_walk(self):
		"""create the walk"""

		while len(self.x_values)<self.num_points:	

			#decide direction
			x_direction=choice([1,-1])
			x_step=choice([1,2,3,4])
			x_walk=x_direction*x_step

			y_direction=choice([1,-1])
			y_step=choice([1,2,3,4])
			y_walk=y_direction*y_step

			self.x_values.append(self.x_values[-1] + x_walk)
			self.y_values.append(self.y_values[-1] + y_walk)
