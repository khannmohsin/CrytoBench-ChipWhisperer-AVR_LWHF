import pandas as pd
import numpy as np
import scipy.stats as stats

# Load the CSV file
file_path = "/Users/khannmohsin/Chipwhispere_vscode/Measurements/power.csv"  # Change this to your actual file path
df = pd.read_csv(file_path)

# Function to calculate 95% confidence interval
def confidence_interval(data):
    data = np.array(data, dtype=np.float64)
    mean = np.mean(data)
    sem = stats.sem(data)  # Standard Error of Mean
    ci = stats.t.interval(0.95, len(data)-1, loc=mean, scale=sem)
    error = ci[1] - mean  # Margin of error


    # Round values to three decimal places
    mean = round(mean, 2)
    ci = (round(ci[0], 2), round(ci[1], 3))
    error = round(error, 2)

    return mean, ci, error

# Process the dataset
results = []
for _, row in df.iterrows():
    hash_function = row['Hash Function']
    variant = row['Variant']
    
    # Convert Power values from string to list of floats
    power_values = list(map(float, row['Energy'].split(',')))

    # Calculate mean and confidence interval
    mean_power, ci_power, error_power = confidence_interval(power_values)
    
    results.append([hash_function, variant, mean_power, ci_power, error_power])

# Convert results to DataFrame
results_df = pd.DataFrame(results, columns=['Hash Function', 'Variant', 'Mean Power', '95% Confidence Interval', 'Error'])

# Display results
print("Power Analysis Results")
print(results_df)