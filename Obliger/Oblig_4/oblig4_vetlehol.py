import numpy as np
import matplotlib.pyplot as plt

# OPPGAVE 1.1

# Definerer konstanter.
I0 = 1e-12 
k = 1.38064852e-23
q = 1.6020e-19
T = 300
V = np.linspace(0, 1.4, 100)

# Idealitetsfaktor for diode 1.
n1 = 1.6

# Idealitetsfaktor for diode 2.
n2 = 1.3

I = I0*(np.exp((q*V)/(n1*k*T))-1)
I2 = I0*(np.exp((q*V)/(n2*k*T))-1)

# Plotter 
plt.plot(V,I, label = "n = 1.6")
plt.plot(V,I2, label = "n = 1.3")
plt.ylim(0,2)
plt.title("Stroem plottet som funksjon av spenning")
plt.xlabel("Spenning [V]")
plt.ylabel("Stroem [A]")
plt.legend()
plt.show()

V_d = 1.14

# OPPGAVE 1.2
print("Stroemmen gjennom dioden med en konstant spenningskilde paa 1.14 Volt er: ", I0*(np.exp((q*V_d)/(n1*k*T))-1))

# OPPGAVE 2
print("Stroemmen gjennom diode 2 med en konstant spenningskilde paa 1.14 Volt er: ", I0*(np.exp((q*V_d)/(n2*k*T))-1))

# OPPGAVE 5.1
Vdd = 10
Vd = 1.14
R = 9

for i in range(1,100000):
    I = I0*(np.exp((q*Vd)/(n1*k*T))-1)
    Vr = I*R

    if Vdd - Vr > Vd:
        Vd += 0.00001
    else:
        Vd -= 0.00001

print("Stroemmen gjennom dioden er her: ", I, "Spenningen er: ", Vd)

# OPPGAVE 5.2
for i in range(1,100000):

    I = I0*(np.exp((q*Vd)/(n2*k*T))-1)
    Vr = I*R

    if Vdd - Vr > Vd:
        Vd += 0.00001
    else:
        Vd -= 0.00001

print("Stroemmen gjennom dioden er her: ", I, "Spenningen er: ", Vd)