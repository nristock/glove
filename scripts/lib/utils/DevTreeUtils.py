from os import environ, path


class DevTree:
    dev_root = ''
    source_dir = ''
    gen_dir = ''
    dbg_build_dir = ''
    opt_build_dir = ''

    @classmethod
    def init_paths(cls, dev_root=environ['GLOVE_DEV_ROOT'], gen_dir=path.join(dev_root, 'gen')):
        cls.dev_root = dev_root
        cls.source_dir = path.join(cls.dev_root, 'src')

        cls.gen_dir = gen_dir
        cls.dbg_build_dir = path.join(cls.gen_dir, 'dbg')
        cls.opt_build_dir = path.join(cls.gen_dir, 'opt')

DevTree.init_paths()
