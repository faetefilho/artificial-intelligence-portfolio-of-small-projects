from car import ElectricCar, Car

my_tesla=ElectricCar('tesla','model 3',2019)
my_bettle=Car('volgswagen','bettle',2019)
print(my_bettle.get_descriptive_name())
print(my_tesla.get_descriptive_name())
my_tesla.battery.describe_battery()
my_tesla.battery.get_range()