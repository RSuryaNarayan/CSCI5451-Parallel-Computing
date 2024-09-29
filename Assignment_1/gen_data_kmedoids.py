import numpy as np
from sklearn_extra.cluster import KMedoids
import random

# Set random seed for reproducibility
np.random.seed(42)
random.seed(42)

# Define parameters for dataset creation
N = 10  # Number of data points
D = 3  # Dimensionality of each point

# Create random 3-dimensional data points
data_points = np.round(np.random.uniform(10, 100, size=(N, D)), decimals=1)
# print(data_points.shape)

# Save the data in the required format
data_text = f"{N} {D}\n" + "\n".join(" ".join(map(str, point)) for point in data_points)
# print(data_text)

# Save to file
file_path = "/Users/surya/Desktop/Intro_to_Parallel_Computing/Assignment_1/km_test_data.txt"
with open(file_path, 'w') as file:
    file.write(data_text)

# Perform k-medoids clustering with k=2 (2 clusters as an example)
k = 2
kmedoids = KMedoids(n_clusters=k, random_state=42).fit(data_points)
cluster_assignments = kmedoids.labels_

# Save cluster assignments to clusters.txt
with open('clusters.txt', 'w') as f:
    for assignment in cluster_assignments:
        f.write(f"{assignment}\n")

# Save medoids to medoids.txt
medoids = kmedoids.cluster_centers_
with open('medoids.txt', 'w') as f:
    for medoid in medoids:
        f.write(f"{' '.join(map(str, medoid))}\n")
