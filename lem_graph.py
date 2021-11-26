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
            print(f"Error: lem-in returned an error:\n{lem_out[0]}")
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

        for i, line in enumerate(lem_input):
            if line.strip('\n').isdigit():
                self.ants = int(line)
                continue
            # check if we have a comment or a command
            if line[0] == '#':
                if line.strip('\n') == "##start":
                    self.source = lem_input[i + 1].split()[0]
                if line.strip('\n') == "##end":
                    self.sink = lem_input[i + 1].split()[0]
                continue
            # store edges separately
            if '-' in line:
                self.edges.append(tuple(line.split('-')))
            # stop when we hit the empty line that separates graph data and moves
            elif line.isspace():
                break
            # store rooms in a dict, with the room name as the key and its coordinates as the value (a tuple)
            node = line.split(' ')
            self.nodes[node[0]] = tuple(node[1:])

    def store_moves(self, move_list):
        if not move_list:
            print(f"lem-in output did not contain the moves. Moves not stored in {self.label}.move_list")
        else:
            # TODO: store individual ants' moves
            pass
