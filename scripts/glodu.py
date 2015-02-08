from argparse import ArgumentParser
from os import path, getcwd
import sys
from lib.utils.Logger import Log

from lib.commands.format import execute_command as cmd_format
from lib.commands.bootstrap import execute_command as cmd_bootstrap
from lib.commands.mkuuid import execute_command as cmd_mkuuid
from lib.commands.build_deps import execute_command as cmd_build_deps

SCRIPT_DIR = path.dirname(path.realpath(__file__))
WORKING_DIR = getcwd()


def parse_args():
    argument_parser = ArgumentParser(description="Glove Development Utils")

    sub_parsers = argument_parser.add_subparsers(title="Sub Commands", help="Commands")

    bootstrap_parser = sub_parsers.add_parser('bootstrap', help="Bootstraps development directory structure")
    bootstrap_parser.set_defaults(func=cmd_bootstrap)
    bootstrap_parser.add_argument('--cmake_debug', '-d',
                                  help="Generates debug build files using cmake",
                                  action='store_const',
                                  const=True,
                                  default=False)
    bootstrap_parser.add_argument('--cmake_release', '-r',
                                  help="Generates release build files using cmake",
                                  action='store_const',
                                  const=True,
                                  default=False)

    format_parser = sub_parsers.add_parser('format', help="Recursively formats sources starting at in cwd")
    format_parser.set_defaults(func=cmd_format)
    format_parser.add_argument('--list_files', '-l',
                               help="List files to format",
                               action='store_const',
                               const=True,
                               default=False)

    mkuuid_parser = sub_parsers.add_parser('mkuuid', aliases=['uuid'], help="Generated a random UUID")
    mkuuid_parser.set_defaults(func=cmd_mkuuid)

    build_deps_parser = sub_parsers.add_parser('build_deps', aliases=['deps'], help="Build Glove engine dependencies")
    build_deps_parser.set_defaults(func=cmd_build_deps)

    argument_parser.add_argument(
        '--verbosity',
        help="Verbosity level (0=Errors only, 1=Info and error messages, 2=All messages",
        type=int,
        default=1)

    return argument_parser.parse_args()

if __name__ == '__main__':
    args = parse_args()
    Log.set_verbosity(args.verbosity)

    if not callable(args.func):
        Log.error('Invalid command')
        sys.exit(1)

    args.func(args)
