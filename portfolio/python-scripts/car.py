"""simulate a car"""
class Car:
	"""Simple attempt to represetn a car"""

	def __init__(self,make,model,year):
		"""Initialize attributes to desc. a car"""
		self.make=make
		self.model=model
		self.year=year
		self.odometer_reading=0

	def get_descriptive_name(self):
		"""Return a neatly formatted descriptive name"""
		long_name=f"{self.year} {self.make} {self.model}"
		return long_name.title()

	def read_odometer(self):
		"""print odo reading"""
		print(f"the car has {self.odometer_reading} miles on it")

	def update_odometer(self,milage):
		"""dont allow rollback odometer"""
		if milage<self.odometer_reading:
			print("not allowed to roll back")
		else:
			self.odometer_reading=milage

	def increment_odometer(self,miles):
		"""increment odo"""
		self.odometer_reading+=miles

class Battery:
	"""model cars battery, init attributes"""
	def __init__(self, battery_size=75):
		"""init batt size"""
		self.battery_size=battery_size

	def describe_battery(self):
		print(f" This car has {self.battery_size} KWh batt")

	def get_range(self):
		if self.battery_size==75:
			range=260
		if self.battery_size==100:
			range=315
		print(f"range is {range} on a full charge")

class ElectricCar(Car):

	def __init__(self, make,model,year):
		super().__init__(make,model,year)
		self.battery=Battery()