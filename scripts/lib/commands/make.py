from lib.utils.DevTreeUtils import DevTree
from lib.utils.Logger import Log
from lib.utils.ProcessUtils import ExecutableRunner


def execute_command(args):
    build_type = args.type

    if build_type == 'dbg':
        build_dir = DevTree.dbg_build_dir
    elif build_type == 'opt':
        build_dir = DevTree.opt_build_dir
    else:
        raise RuntimeError('Invalid build type.')

    make_process = ExecutableRunner('make', ['-j8', args.target], build_dir,
                                    lambda: Log.info('Built {0} Glove: {1}'.format(args.type, args.target)),
                                    lambda: Log.error('Build failed'))
    make_process.run()

    if args.install:
        install_process = ExecutableRunner('sudo', ['make', 'install'], build_dir, lambda: Log.info(
            'Installed {0} Glove'.format(args.type)), lambda: Log.error('Install failed'))
        install_process.run()


def setup_args(parser):
    parser.add_argument('type', choices=['dbg', 'opt'], help="The build type")
    parser.add_argument('target', nargs='?', type=str, default='all', help="Build target")
    parser.add_argument('--install', '-i', action='store_const', const=True, default=False, help='Install Glove')

