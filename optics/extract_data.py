import re
pH_pattern = re.compile(r"\d+\.\d+")
measurement_pattern = re.compile(r"back: (?P<back>\d+\.\d+), R: (?P<red>\d+\.\d+), G: (?P<green>\d+\.\d+), B: (?P<blue>\d+\.\d+)")
pH = None
while True:
   line = None
   try:
      line = raw_input()
   except:
      break
   if not line: continue
   if pH_pattern.match(line):
      pH = float(line[:-1])
   else:
      #print(line)
      m = measurement_pattern.match(line)
      if not m: 
         print('Error parsing')
         continue
      print('{0} {1} {2} {3} {4}'.format(pH, m.group('back'), m.group('red'), m.group('green'), m.group('blue')))