import numpy as np

def print_stats(vals):
    vals = np.array(vals)
    print("Mean: {0}, Std: {1}, Num: {2}".format(np.mean(vals), np.std(vals), len(vals)))

if __name__ == '__main__':
    vals = []

    while True:
        try:
            s = input()
        except:
            break
        if s == 'END':
            break
        try:
            val = int(s)
        except:
            if len(vals) > 0:
                print_stats(vals)
            vals = []
            print(s)
            continue
        vals.append(val)