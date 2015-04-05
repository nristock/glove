from os import getcwd, path

from lib.utils.DevTreeUtils import DevTree
from lib.utils.Logger import Log
from lib.utils.SourceUtils import iterate_sources
from lib.utils.ProcessUtils import ExecutableRunner


def execute_command(args):
    Log.info("Starting code formatting...")

    clang_format_command = '-i'.split(' ')
    working_dir = getcwd()

    if working_dir == DevTree.dev_root:
        working_dir = DevTree.source_dir

    for cc_file in iterate_sources('*.cc', working_dir):
        if args.list_files:
            Log.info("Formatting {0}".format(path.relpath(cc_file, working_dir)))
        clang_format_command.append(cc_file)

    for hpp_file in iterate_sources('*.h', working_dir):
        if args.list_files:
            Log.info("Formatting {0}".format(path.relpath(hpp_file, working_dir)))
        clang_format_command.append(hpp_file)

    clang_format_runner = ExecutableRunner('clang-format', clang_format_command, working_dir,
                                           lambda: (Log.info("Successfully formatted sources")),
                                           lambda: (Log.error("Source formatting failed")))
    clang_format_runner.run()

    Log.info("Done.")


def setup_args(parser):
    parser.add_argument('--list_files', '-l',
                        help="List files to format",
                        action='store_const',
                        const=True,
                        default=False)
