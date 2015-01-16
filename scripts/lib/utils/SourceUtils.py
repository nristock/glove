from lib.utils.DevTreeUtils import DevTree
import os
import fnmatch
from lib.utils.Logger import Log


def iterate_sources(fn_filter, root=DevTree.source_dir):
    for root, dir_names, file_names in os.walk(root):
        for filename in fnmatch.filter(file_names, fn_filter):
            yield os.path.join(root, filename)
