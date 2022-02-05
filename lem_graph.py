class Antfarm:
    """
    Parses and stores lem-in graph data and moves of its output.

    @lem_output is the filepath of the output of lem-in
    """

    def __init__(self, lem_output, moves=True):
        self.label = self.__class__.__name__
        self.moves = moves
        self.lem_input = []
        self.move_list = []
        self.nodes = {}
        self.edges = []
        self.source = ""
        self.sink = ""
        self.ants = 0
        self.ant_moves = {}
        self.separate_output(lem_output)
        self.store_graph(self.lem_input)
        self.store_moves(self.move_list)

    def separate_output(self, lem_output):
        # read lem-in's output file to a list
        try:
            with open(lem_output, "r") as f:
                lem_out = []
                for line in f:
                    lem_out.append(line)
        except FileNotFoundError:
            print(f"Error: File '{lem_output}' not found")
            quit(-1)

        if "ERROR" in lem_out[0]:
            print(f"lem-in returned an error:\n{lem_out[0]}")
            quit()

        if self.moves:
            # split lem-in's input and moves based on the empty line between them
            for i, line in enumerate(lem_out):
                if line.isspace():
                    self.lem_input = lem_out[:i]
                    self.move_list = lem_out[i + 1:]
                    break
            # if no empty line in the (middle of) output, it's not properly formatted
            if len(self.lem_input) == 0 or len(self.move_list) == 0:
                print("Output of lem-in not split properly with an empty line")
                quit()
        else:
            self.lem_input = lem_out

    def store_graph(self, lem_input):

        def check_node(split_line):
            if len(split_line) != 3:
                print("Too many spaces!")
                return False
            if not split_line[1].isdigit() or not split_line[2].isdigit():
                print("Coordinates not numbers!")
                return False
            if split_line[0][0] == 'L':
                print("Room cannot start with an 'L'!")
                return False
            return True

        # get the number of ants
        if lem_input[0].strip('\n').isdigit():
            self.ants = int(lem_input[0])
        else:
            print("First line of output isn't the number of ants like it's supposed to")
            quit()

        room_end_line = 0
        for i, line in enumerate(lem_input[1:]):
            # check if we have a comment or a command
            if line[0] == '#':
                if line.strip('\n') == "##start" and len(lem_input) > i + 2:
                    self.source = lem_input[i + 2].split()[0]
                elif line.strip('\n') == "##end" and len(lem_input) > i + 2:
                    self.sink = lem_input[i + 2].split()[0]
                continue
            # stop when we hit a line with a '-' or an empty line
            if line.isspace() or '-' in line:
                room_end_line = i + 1
                break
            # store rooms in a dict, with the room name as the key and its coordinates as the value (a tuple)
            node = line.strip('\n').split(' ')
            if check_node(node):
                self.nodes[node[0]] = tuple(node[1:])
            else:
                print(f"Invalid room (line {i + 2}):\n{line}")
                quit()

        if room_end_line == 0:  # empty line encountered in a wrong place (should be after links/tubes)
            print("No links/tubes found after rooms")
            quit()
        if not self.source or not self.sink:
            print("Didn't find both ##start and ##end in input")
            quit()
        if '-' not in lem_input[room_end_line]:
            print(f"Invalid link (line {room_end_line + 1}):\n{lem_input[room_end_line]}")
            quit()

        edges_start = room_end_line
        for i, line in enumerate(lem_input[edges_start:]):
            if line[0] == '#':
                continue
            edge = line.strip('\n').split('-')
            if len(edge) != 2:
                print(f"Invalid link (line {edges_start + i + 1}):\n{line}")
                quit()
            if edge[0] not in self.nodes.keys():
                print(f"Unknown room name encountered in links (line {edges_start + i + 1}):\n{edge[0]}")
                quit()
            if edge[1] not in self.nodes.keys():
                print(f"Unknown room name encountered in links (line {edges_start + i + 1}):\n{edge[1]}")
                quit()
            self.edges.append(tuple(edge))

    def store_moves(self, move_list):
        if not move_list:
            print(f"lem-in output did not contain the moves. Moves not stored in {self.label}.move_list")
        else:
            # TODO: store individual ants' moves
            for i, move in enumerate(move_list):
                ant_steps = move.strip('\n').split(' ')
                for a_step in ant_steps:
                    step = a_step.split('-')
                    if len(step) != 2:
                        print(f"Move formatted incorrectly (turn {i + 1}):\n{move}")
                        quit()
                    try:
                        ant_num = int(step[0][1:])
                        if ant_num <= 0 or ant_num > self.ants:
                            print(f"Invalid ant number (turn {i + 1}):\n{move}")
                            quit()
                    except:
                        print(f"Move formatted incorrectly (turn {i + 1}):\n{move}")
                        quit()

                    if step[0] not in self.ant_moves.keys():
                        self.ant_moves[step[0]] = [step[1]]
                    else:
                        self.ant_moves[step[0]].append(step[1])
