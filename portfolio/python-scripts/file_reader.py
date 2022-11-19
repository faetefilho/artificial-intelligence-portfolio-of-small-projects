filename='pi_million_digits.txt'
with open(filename) as file_object:
	contents=file_object.readlines()
	
pi_string=''

for line in contents:
	pi_string+=line.strip()

bday=input('enter mmddyy: ')
if bday in pi_string:
	print('bday in pi')
else:
	print('bday not in pi')
	
# print(pi_string)
#print(f"{pi_string[:10]}")
# print(contents.rstrip())