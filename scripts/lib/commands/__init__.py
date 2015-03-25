from lib.commands.CommandRegistry import CommandRegistry as CmdReg, Command


def _register(name, help, command, generate_args=None, aliases=list()):
    CmdReg.register_command(Command(name, help, command, generate_args, aliases))


def _cmd_bootstrap(args):
    from lib.commands import bootstrap

    bootstrap.execute_command(args)


def _cmd_build_deps(args):
    from lib.commands import build_deps

    build_deps.execute_command(args)


def _cmd_format(args):
    from lib.commands import format

    format.execute_command(args)


def _cmd_keys(args):
    from lib.commands import gen_keys

    gen_keys.execute_command(args)


def _cmd_rhi(args):
    from lib.commands import gen_rhicmd

    gen_rhicmd.execute_command(args)


def _cmd_make(args):
    from lib.commands import make

    make.execute_command(args)


def _cmd_uuid(args):
    from lib.commands import mkuuid

    mkuuid.execute_command(args)


def _args_bootstrap(parser):
    from lib.commands import bootstrap

    bootstrap.setup_args(parser)


def _args_format(parser):
    from lib.commands import format

    format.setup_args(parser)


def _args_keys(parser):
    from lib.commands import gen_keys

    gen_keys.setup_args(parser)


def _args_make(parser):
    from lib.commands import make

    make.setup_args(parser)


_register('bootstrap', 'Bootstraps development directory structure', _cmd_bootstrap, generate_args=_args_bootstrap)
_register('build_deps', 'Builder Globe Engine Dependencies', _cmd_build_deps, aliases=['deps'])
_register('format', 'Recursively formats sources starting at cwd', _cmd_format, generate_args=_args_format)
_register('keys', 'Generates the input keys', _cmd_keys, generate_args=_args_keys)
_register('rhi', 'Generates RHI commands the the RHI interface', _cmd_rhi)
_register('make', 'Builds Glove', _cmd_make, generate_args=_args_make, aliases=['build'])
_register('mkuuid', 'Generates a reandom UUID', _cmd_uuid, aliases=['uuid'])
