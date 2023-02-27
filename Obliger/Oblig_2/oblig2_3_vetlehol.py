import matplotlib.pyplot as plt
import numpy as np

R2 = 150 #Ohm
V1 = 10 #V
R1 = np.linspace(1,1000,1000) #Ohm
V_ut = (V1 * R1) / (R1 + R2) #V

plt.plot(R1,V_ut)
plt.title("Spenning over R1 som funksjon av motstanden i R1")
plt.xlabel("Motstand R1 [Ohm]")
plt.ylabel("Spenning over motstand R1 [V]")
plt.show()
