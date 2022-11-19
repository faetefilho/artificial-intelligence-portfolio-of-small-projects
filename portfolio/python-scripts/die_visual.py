from die import Die
from plotly.graph_objs import Bar, Layout
from plotly import offline


die=Die()
results=[]

for die_row in range(1000):
	results.append(die.roll())

# print(results)
print(len(results))

#analize the results

frequencies=[]

for num in range(1,die.num_sides+1):
	frequencies.append(results.count(num))

print(frequencies)

#Visualize results
x_values=list(range(1,die.num_sides+1))
data= [Bar(x=x_values,y=frequencies)]

x_axis_config={'title':'Result'}
y_axis_config={'title':'Frequency of Results'}

my_layout = Layout(title='Results of rolling a D6 1000 times',xaxis=x_axis_config, yaxis=y_axis_config)

offline.plot({'data':data,'layout':my_layout},filename='d6.html')
