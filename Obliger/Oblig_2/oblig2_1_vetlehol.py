import matplotlib.pyplot as plt
import numpy as np

volt = np.arange(1,10.1,0.1) # 1 til 10, step = 0.1.
ohm = 100 # Motstanden
ampere = volt/ohm # Uttrykk for stroemmen gjennom motstanden.

# Plotter spenning langs x-aksen, stroem langs y-aksen. 
plt.plot(volt,ampere)
plt.title("Stroem gjennom en 100 ohm motstand")
plt.xlabel("Spenning [Volt]")
plt.ylabel("Strøm [Ampere]")
plt.grid()
plt.show()

