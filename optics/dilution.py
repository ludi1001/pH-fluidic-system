import math
K_w = 1e-14
def acid_concentration_to_pH(acid_conc):
    x = 1e-7 + acid_conc/2 - math.sqrt(K_w + acid_conc**2 / 4)
    H_conc = 1e-7 + acid_conc - x #acid_conc/2 + math.sqrt(K_w + acid_conc**2 / 4)
    return -math.log10(H_conc)

def pH_to_acid_concentration(pH):
    H_conc = 10**(-pH)
    return H_conc - K_w/H_conc
    
def dilution_pH(pH, sample_volume, water_volume):
    acid_conc = pH_to_acid_concentration(pH)
    #print('original [HCl]: {0}'.format(acid_conc))
    new_acid_conc = acid_conc * sample_volume / (sample_volume + water_volume)
    #print('new [HCl]: {0}'.format(new_acid_conc))
    return acid_concentration_to_pH(new_acid_conc)

def test_funcs():    
    conc = [1e-7, 2e-7, 1e-8, 1e-6, 1e-2]
    for c in conc:
        pH = acid_concentration_to_pH(c)
        print('{0}: {1}, {2}'.format(c, pH, pH_to_acid_concentration(pH)))
        
for i in range(10):
    pH = 6 + i/10
    print(dilution_pH(pH, 40, 40))