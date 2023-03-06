import matplotlib.pyplot as plt
# Open the output file and read the coordinates
with open('output.txt', 'r') as f:
    lines = f.readlines()
    polygons = []
    current_polygon = []
    for line in lines:
        if line.strip() == 'end':
            current_polygon.append(current_polygon[0])  # join first and last coordinate
            polygons.append(current_polygon)
            current_polygon = []
        else:
            # Split the line into x and y coordinates
            x, y = map(float, line.strip().split(','))
            current_polygon.append((x, y))
    if current_polygon:  # append last polygon
        current_polygon.append(current_polygon[0])  # join first and last coordinate
        polygons.append(current_polygon)

# Plot each polygon using matplotlib
plt.subplot(1,3,1)
for polygon in polygons:
    x, y = zip(*polygon)  # unzip the list of tuples into separate x and y lists
    plt.plot(x, y)


with open('output2.txt', 'r') as f:
    lines = f.readlines()
    polygons = []
    current_polygon = []
    for line in lines:
        if line.strip() == 'end':
            current_polygon.append(current_polygon[0])  # join first and last coordinate
            polygons.append(current_polygon)
            current_polygon = []
        else:
            # Split the line into x and y coordinates
            x, y = map(float, line.strip().split(','))
            current_polygon.append((x, y))
    if current_polygon:  # append last polygon
        current_polygon.append(current_polygon[0])  # join first and last coordinate
        polygons.append(current_polygon)

# Plot each polygon using matplotlib
plt.subplot(1,3,2)
for polygon in polygons:
    x, y = zip(*polygon)  # unzip the list of tuples into separate x and y lists
    plt.plot(x, y,marker =".")

with open('output3.txt', 'r') as f:
    lines = f.readlines()
    polygons = []
    current_polygon = []
    for line in lines:
        if line.strip() == 'end':
            current_polygon.append(current_polygon[0])  # join first and last coordinate
            polygons.append(current_polygon)
            current_polygon = []
        else:
            # Split the line into x and y coordinates
            x, y = map(float, line.strip().split(','))
            current_polygon.append((x, y))
    if current_polygon:  # append last polygon
        current_polygon.append(current_polygon[0])  # join first and last coordinate
        polygons.append(current_polygon)

# Plot each polygon using matplotlib
plt.subplot(1,3,3)
for polygon in polygons:
    x, y = zip(*polygon)  # unzip the list of tuples into separate x and y lists
    plt.plot(x, y)
# plt.show()
plt.savefig("op.png")
