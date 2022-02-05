#!/usr/bin/env python3

import sys
import re
from lem_graph import Antfarm


def color_collision(turn, dup_list):
    colors = ['31', '32', '33', '34', '35', '36', '37']
    for i, potential_duplicate in enumerate(dup_list):
        if potential_duplicate in dup_list[i+1:]:
            turn = re.sub(potential_duplicate,
                          f"\033[0;{colors[i % len(colors)]}m" + potential_duplicate + "\033[0m",
                          turn
                          )
    return turn


def verify_moves(total_ants, sink, move_list):
    """Checks that the output of lem-in is formatted properly and that the moves are valid"""

    err = False
    moved_ants = []
    used_rooms = []
    # go through moves line by line (aka turn by turn)
    for n, turn in enumerate(move_list):
        moves = turn.strip().split(' ')
        ants_per_turn = []
        rooms_per_turn = []
        # store each moved ant and the rooms they entered to their own lists
        for move in moves:
            move = move.split('-')
            ants_per_turn.append(move[0] + '-')  # dash appended in order to keep color_collision() general purpose
            rooms_per_turn.append(move[1])
        # add the ants/rooms that were moved/entered to overall progression tracking lists
        moved_ants += ants_per_turn
        used_rooms += rooms_per_turn
        # check that only unique ants moved on this turn
        if len(ants_per_turn) != len(list(set(ants_per_turn))):
            turn = color_collision(turn, ants_per_turn)
            print(f"Same ant moved twice on a single turn!\nTurn #{n}\n{turn}\n")
            err = True
        # chech that rooms entered on this turn were vacant
        if sink not in rooms_per_turn and len(rooms_per_turn) != len(list(set(rooms_per_turn))):
            turn = color_collision(turn, rooms_per_turn)
            print(f"Multiple ants in same room!\nTurn #{n}\n{turn}\n")
            err = True

    # after going through all turns, check that all ants were moved
    if len(list(set(moved_ants))) != total_ants:
        print(f"Incorrect amount of ants moved! {len(list(set(moved_ants)))} != {total_ants}")

    return used_rooms, err


def verify_paths(g, rooms_used, err):
    if len(rooms_used) == 0:
        print("There should have been at least one error message by now. Quitting...")
        quit()
    for room in rooms_used:
        if room not in g.nodes:
            print(f"Room '{room}' doesn't exist in input!")
            quit()
    finished_ants = []
    for ant in g.ant_moves.keys():
        path = g.ant_moves[ant]
        if path[-1] != g.sink:
            print(f"Ant {ant} doesn't reach the sink! Last room it enters is {path[-1]}")
            err = True
        for i, room in enumerate(path):
            if i == 0:
                if (room, g.source) not in g.edges and (g.source, room) not in g.edges:
                    print(f"There isn't a connection between {g.source} and {room}")
                    err = True
            elif (room, path[i - 1]) not in g.edges and (path[i - 1], room) not in g.edges:
                print(f"There isn't a connection between {path[i - 1]} and {room}. (culprit ant: {ant})")
                err = True
            elif room == g.sink:
                if ant not in finished_ants:
                    finished_ants.append(ant)
                else:
                    print(f"Ant {ant} moved after reaching sink!")
                    err = True
    if len(finished_ants) != g.ants:
        print(f"All ants didn't reach sink! {len(finished_ants)} != g.ants")
        err = True
    return err


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <lem-in_output_file>")
        quit()

    g = Antfarm(sys.argv[1])
    rooms_used, err = verify_moves(g.ants, g.sink, g.move_list)
    err = verify_paths(g, rooms_used, err)
    if not err:
        print("Moves are valid!")


if __name__ == "__main__":
    main()
