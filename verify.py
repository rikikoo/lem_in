#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print(f"Usage: [python3] {sys.argv[0]} <lem-in_output_file>")
    quit()

filepath = sys.argv[1]

# read outfile to list
try:
    with open(filepath, "r") as f:
        lem_out = []
        for line in f:
            lem_out.append(line)
except Exception:
    print(f"Error: {Exception}\nUsage: [python3] {sys.argv[0]} <lem-in_output_file>")
    raise

# store total ants, sink, and moves
ants = int(lem_out[0])
move_list = []
sink = None
for i, line in enumerate(lem_out):
    if "##end" in line:
        sink = lem_out[i + 1].split()[0]
        continue
    if line[0] == 'L':
        move_list = lem_out[i:]
        break

err = False
for turn in move_list:
    moves = turn.strip().split(' ')
    ants = []
    rooms = []
    for move in moves:
        ants.append(move.split('-')[0][1:])
        rooms.append(move.split('-')[1])
    if len(ants) != len(list(set(ants))):
        for i, ant in enumerate(ants):
            if ant in ants[i + 1:]:
                print(f"Same ant moved twice on a single turn ({ant})!\n{turn}\n")
                err = True
                break
    if sink not in rooms and len(rooms) != len(list(set(rooms))):
        for i, room in enumerate(rooms):
            if room in rooms[i + 1:]:
                print(f"Multiple ants in same room ({room})!\n{turn}\n")
                err = True
                break

if err == False:
    print("Moves are valid!")