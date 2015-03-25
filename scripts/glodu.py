from argparse import ArgumentParser
from os import path, getcwd
import sys
from lib.commands.CommandRegistry import CommandRegistry
from lib.utils.Logger import Log

SCRIPT_DIR = path.dirname(path.realpath(__file__))
WORKING_DIR = getcwd()


def parse_args():
    argument_parser = ArgumentParser(description="Glove Development Utils")

    sub_parsers = argument_parser.add_subparsers(title="Sub Commands", help="Commands")
    CommandRegistry.init_parsers(sub_parsers)

    argument_parser.add_argument(
        '--verbosity',
        help="Verbosity level (0=Errors only, 1=Info and error messages, 2=All messages",
        type=int,
        default=1)

    return argument_parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    Log.set_verbosity(args.verbosity)

    if not callable(args.execute):
        Log.error('Invalid command')
        sys.exit(1)

    args.execute(args)
