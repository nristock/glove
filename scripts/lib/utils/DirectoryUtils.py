import os


def ensure_exists(dir_path):
    if not os.path.isdir(dir_path):
        os.makedirs(dir_path)
