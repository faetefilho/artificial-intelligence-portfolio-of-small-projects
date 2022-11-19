import matplotlib.pyplot as plt
from random_walk import RandomWalk

rw=RandomWalk(50_000)
rw.fill_walk()

#plot the point in the random walk
plt.style.use('classic')

fig, ax = plt.subplots(figsize=(15,9))

point_numbers=range(rw.num_points)
ax.scatter(rw.x_values, rw.y_values, c=point_numbers, cmap=plt.cm.Blues, edgecolors='none', s=1)
#emphasize first and last points
ax.scatter(0,0,c='green',edgecolors='none', s=100)
ax.scatter(rw.x_values[-1],rw.y_values[-1], c='red', edgecolors='none', s=100)
#remove axis
ax.get_xaxis().set_visible(False)
ax.get_yaxis().set_visible(False)

plt.show()