import sys

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} <lem-in_output_file>")
    quit()

filepath = sys.argv[1]

# read outfile to list
try:
    with open(filepath, "r") as f:
        lem_out = []
        for line in f:
            lem_out.append(line)
except:
    print(f"Usage: {sys.argv[0]} <lem-in_output_file>")
    quit()

# store total ants, sink, and moves
ants = int(lem_out[0])

for i, line in enumerate(lem_out):
    if line == "##end":
        sink = lem_out[i + 1]
        continue
    if line[0] == 'L':
        moves = lem_out[i:]
        break

for turn in moves:
    for 
