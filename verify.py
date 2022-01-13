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

    if not err:
        # after going through all turns, check that all ants were moved
        if len(list(set(moved_ants))) != total_ants:
            print(f"All ants not moved! {len(list(set(moved_ants)))} < {total_ants}")
        else:
            print("Moves are valid!")

    return used_rooms


def verify_paths(g, rooms_used):
    # TODO: check individual ants' paths and make sure that
    #   - all ants start from rooms linked to g.source
    #   - all ants end up in g.sink
    #   - the rooms they travel are linked as per g.edges

    if len(rooms_used) == 0:
        print("There should have been at least one error message by now...")


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <lem-in_output_file>")
        quit()

    g = Antfarm(sys.argv[1])
    rooms_used = verify_moves(g.ants, g.sink, g.move_list)
    verify_paths(g, rooms_used)


if __name__ == "__main__":
    main()
