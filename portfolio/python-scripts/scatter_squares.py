import matplotlib.pyplot as plt 

plt.style.use('seaborn')
x_values=range(1,1001)
y_values=[x**2 for x in x_values]

fig,ax=plt.subplots()
ax.scatter(x_values,y_values,c='red',s=10)
#title and label
ax.set_title('Square Numbers',fontsize=24)
ax.set_xlabel('numbers',fontsize=14)
ax.set_ylabel('squares',fontsize=14)
#tick size
ax.tick_params(axis='both',which='major',labelsize=14)
ax.axis([0, 1100,0, 1100000 ])
plt.show()