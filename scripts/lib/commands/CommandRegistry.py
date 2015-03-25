class Command:
    def __init__(self, name, help, on_execute, generate_parser_args=None, aliases=list()):
        self.name = name
        self.help = help
        self.on_execute = on_execute
        self.generate_parser_args = generate_parser_args
        self.aliases = aliases

    def generate_parser(self, sub_parsers):
        parser = sub_parsers.add_parser(self.name, aliases=self.aliases, help=self.help)
        parser.set_defaults(execute=self.on_execute)

        if self.generate_parser_args:
            self.generate_parser_args(parser)


class CommandRegistry:
    commands = []

    @classmethod
    def register_command(cls, command):
        cls.commands += [command]

    @classmethod
    def init_parsers(cls, sub_parsers):
        for command in cls.commands:
            command.generate_parser(sub_parsers)
