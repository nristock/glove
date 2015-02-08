from os import environ, path
import os
from lib.utils.Logger import Log

if not environ['GLOVE_DEV_ROOT']:
    raise RuntimeError("GLOVE_DEV_ROOT environment variable is not set")


class DevTree:
    dev_root = ''
    source_dir = ''
    gen_dir = ''
    dbg_build_dir = ''
    opt_build_dir = ''
    deps_dir = ''
    deps_build_dir = ''
    deps_source_dir = ''
    deps_install_dir = ''

    @classmethod
    def init_paths(cls, dev_root=environ['GLOVE_DEV_ROOT'], gen_dir=None, deps_dir=None, deps_source_suffix='sources', deps_install_suffix=None):
        cls.dev_root = dev_root
        cls.source_dir = path.join(cls.dev_root, 'src')

        cls.gen_dir = gen_dir if gen_dir else path.join(cls.dev_root, 'gen')
        cls.dbg_build_dir = path.join(cls.gen_dir, 'dbg')
        cls.opt_build_dir = path.join(cls.gen_dir, 'opt')

        cls.deps_dir = deps_dir if deps_dir else path.join(cls.dev_root, 'deps')
        cls.deps_build_dir = path.join(cls.deps_dir, 'build')
        cls.deps_source_dir = path.join(cls.deps_dir, deps_source_suffix)

        if not deps_install_suffix:
            # 64bit Windows and Linux are the only supported platform for now
            deps_install_suffix = 'linux64' if os.name == 'posix' else 'win64'

        cls.deps_install_dir = path.join(cls.deps_dir, deps_install_suffix)

DevTree.init_paths()
