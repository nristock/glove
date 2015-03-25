from lib.utils.CMakeGenerator import CMakeGenerator
from lib.utils.DevTreeUtils import DevTree
from lib.utils.DirectoryUtils import ensure_exists


def execute_command(args):
    ensure_exists(DevTree.gen_dir)
    ensure_exists(DevTree.dbg_build_dir)
    ensure_exists(DevTree.opt_build_dir)

    if args.cmake_debug:
        dbg_generator = CMakeGenerator(DevTree.source_dir, DevTree.dbg_build_dir, None, None, 'Debug')
        dbg_generator.run()

    if args.cmake_release:
        opt_generator = CMakeGenerator(DevTree.source_dir, DevTree.opt_build_dir, None, None, 'Release')
        opt_generator.run()


def setup_args(parser):
    parser.add_argument('--cmake_debug', '-d',
                        help="Generates debug build files using cmake",
                        action='store_const',
                        const=True,
                        default=False)
    parser.add_argument('--cmake_release', '-r',
                        help="Generates release build files using cmake",
                        action='store_const',
                        const=True,
                        default=False)

