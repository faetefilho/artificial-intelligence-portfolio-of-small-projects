from die import Die
from plotly.graph_objs import Bar, Layout
from plotly import offline

# Create two D6 dice
die_1=Die()
die_2=Die(10)
results=[]

for die_row in range(50_000):
	results.append(die_1.roll()+die_2.roll())

# print(results)
print(len(results))

#analize the results

frequencies=[]
max_results=die_1.num_sides+die_2.num_sides

for num in range(2,max_results+1):
	frequencies.append(results.count(num))

print(frequencies)

#Visualize results
x_values=list(range(2,max_results+1))
data= [Bar(x=x_values,y=frequencies)]

x_axis_config={'title':'Result','dtick':1}
y_axis_config={'title':'Frequency of Results'}

my_layout = Layout(title='Results of rolling a D6 and D10 50000 times',xaxis=x_axis_config, yaxis=y_axis_config)

offline.plot({'data':data,'layout':my_layout},filename='d6_d10.html')
