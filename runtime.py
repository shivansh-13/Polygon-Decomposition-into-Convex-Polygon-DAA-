# Shivansh Shrivastava 2020A7PS2095H 
# Bhavya Jain 2020A7PS0240H
# Dhruv Agrawal 2020A7PS2193H


import csv
import matplotlib.pyplot as plt

## Read the data from the CSV file
with open('times.csv') as f:
    reader = csv.reader(f)
    data = [float(row[0])/1000 for row in reader]

## Generate values for n from 5 to 30
n_values = range(5,15000)

## Plot the graph
plt.plot(n_values, data)
plt.xlabel('n')
plt.ylabel('Runtime')
plt.title('Runtime vs. n')
plt.show()
plt.savefig("rn.png")
