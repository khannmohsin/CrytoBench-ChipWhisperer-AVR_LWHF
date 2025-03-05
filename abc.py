import matplotlib.pyplot as plt

# Function to generate a 2D lattice
def generate_lattice(basis, x_range, y_range):
    points = []
    for x1 in range(-x_range, x_range):
        for x2 in range(-y_range, y_range):
            point = x1 * basis[:, 0] + x2 * basis[:, 1]
            points.append(point)
    return np.array(points)

# Define basis vectors for two different lattice examples
basis1 = np.array([[2, 3], [5, 7]])
basis2 = np.array([[3, 1], [4, 2]])

# Generate lattice points for each basis
lattice1 = generate_lattice(basis1, 10, 10)
lattice2 = generate_lattice(basis2, 10, 10)

# Define SVP and CVP examples for each lattice
svp_vectors1 = [point for point in lattice1 if not np.array_equal(point, [0, 0])]
shortest_vector1 = min(svp_vectors1, key=lambda v: np.linalg.norm(v))

svp_vectors2 = [point for point in lattice2 if not np.array_equal(point, [0, 0])]
shortest_vector2 = min(svp_vectors2, key=lambda v: np.linalg.norm(v))

cvp_targets1 = [np.array([3, 4]), np.array([6, 9]), np.array([7, 11]), np.array([8, 12])]
cvp_solutions1 = [(target, min(lattice1, key=lambda p: distance.euclidean(p, target))) for target in cvp_targets1]

cvp_targets2 = [np.array([5, 5]), np.array([9, 7]), np.array([10, 12]), np.array([7, 14])]
cvp_solutions2 = [(target, min(lattice2, key=lambda p: distance.euclidean(p, target))) for target in cvp_targets2]

# Create figure with subplots for two lattices
fig, axs = plt.subplots(1, 2, figsize=(12, 6))

# Plot Lattice 1 with SVP and CVP examples
axs[0].scatter(lattice1[:, 0], lattice1[:, 1], color='gray', label='Lattice Points')
axs[0].quiver(0, 0, shortest_vector1[0], shortest_vector1[1], angles='xy', scale_units='xy', scale=1, color='red', label='Shortest Vector (SVP)')

for target, closest in cvp_solutions1:
    axs[0].scatter(target[0], target[1], color='blue', marker='x', s=100, label='Target Point (CVP)')
    axs[0].quiver(closest[0], closest[1], target[0] - closest[0], target[1] - closest[1], angles='xy', scale_units='xy', scale=1, color='green', label='CVP Solution')

axs[0].set_title("Lattice 1: SVP and CVP")
axs[0].axhline(0, color='black', linewidth=0.5)
axs[0].axvline(0, color='black', linewidth=0.5)
axs[0].legend(loc="upper left")
axs[0].grid(True)

# Plot Lattice 2 with SVP and CVP examples
axs[1].scatter(lattice2[:, 0], lattice2[:, 1], color='gray', label='Lattice Points')
axs[1].quiver(0, 0, shortest_vector2[0], shortest_vector2[1], angles='xy', scale_units='xy', scale=1, color='red', label='Shortest Vector (SVP)')

for target, closest in cvp_solutions2:
    axs[1].scatter(target[0], target[1], color='blue', marker='x', s=100, label='Target Point (CVP)')
    axs[1].quiver(closest[0], closest[1], target[0] - closest[0], target[1] - closest[1], angles='xy', scale_units='xy', scale=1, color='green', label='CVP Solution')

axs[1].set_title("Lattice 2: SVP and CVP")
axs[1].axhline(0, color='black', linewidth=0.5)
axs[1].axvline(0, color='black', linewidth=0.5)
axs[1].legend(loc="upper left")
axs[1].grid(True)

# Show the plot
plt.show()