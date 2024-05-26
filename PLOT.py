#%%
import pandas as pd
import matplotlib.pyplot as plt

# %%
data = pd.read_csv("res.csv")
data2 = pd.read_csv("res2.csv")

# %%

# set size to 10
plt.figure(figsize=(10, 5))
# %%

data.plot(x="size")

# %%
data2.plot(x="size")

# %%
