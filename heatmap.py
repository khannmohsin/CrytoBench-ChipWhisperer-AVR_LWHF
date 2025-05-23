import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Step 1: Define the data
data = {
    'LWHF': [
        'PHOTON', 'Lesamnta-LW', 'BLAKE2s', 'BLAKE3', 'ASCON', 'PHOTON-Beetle', 'Xoodyak', 'KNOT',
        'ORANGISH', 'SHAMAS', 'SIV-Rijndael', 'SIV-TEM-PHOTON', 'SKINNY-tk2', 'SNEIKHA', 'TRIAD', 'Coral',
        'Gimli', 'CLX', 'ACE-H', 'ESCH', 'Subterranean', 'Saturnin', 'ISAP', 'GAGE'
    ],
    'CpB': [
        845, 1604, 3516, 2545, 2531, 2158, 2450, 3762, 1207, 3643, 811, 3392, 204, 2533, 3657, 907,
        2256, 1116, 3728, 1633, 4065, 3449, 3953, 3722
    ],
    'RAM': [
        588, 472, 647, 3827, 153, 263, 390, 390, 221, 602, 1417, 343, 559, 345, 423, 268,
        128, 57, 144, 396, 2109, 634, 250, 177
    ],
    'ROM': [
        2708, 3840, 28704, 48072, 2648, 1936, 2804, 3106, 2702, 7954, 1970, 2322, 6806, 6266, 6266, 3612,
        1468, 630, 2076, 3990, 10478, 3732, 4040, 1471
    ],
    'Energy': [
        363.6, 709.21, 1552.09, 1128.06, 1099.3, 950.55, 1058.72, 1613.87, 535.02, 1561.98, 343.67,
        1469.39, 83.87, 1103.14, 1574.24, 396.28, 985.88, 476.28, 1607.12, 719.05, 1759.59,
        1559.53, 1714.84, 1599.83
    ],
    'E-RANK': [
        0.84, 0.18, 0.0061, 0.0063, 0.12, 0.2, 0.11, 0.04, 0.49, 0.02, 0.75, 0.07, 7.38, 0.05, 0.02,
        0.67, 0.26, 2.53, 0.07, 0.18, 0.01, 0.037, 0.032, 0.092
    ]
}

# Step 2: Create a DataFrame
df = pd.DataFrame(data)

# Step 3: Set the 'LWHF' column as the index (for easy labeling in the heatmap)
df.set_index('LWHF', inplace=True)

# Step 4: Normalize the values for visualization (optional, based on scale differences)
normalized_df = (df - df.min()) / (df.max() - df.min())

# Step 5: Plot the heatmap
plt.figure(figsize=(12, 8))  # Set figure size
sns.heatmap(normalized_df, annot=True, cmap='viridis', cbar=True, fmt='.2f', linewidths=0.5)

# Title and labels
plt.title('Heatmap of Normalized Performance Metrics for Lightweight Hash Functions')
plt.ylabel('LWHF')
plt.xlabel('Metrics')

# Show the plot
plt.tight_layout()
plt.show()