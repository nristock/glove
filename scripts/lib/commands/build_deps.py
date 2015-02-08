import fnmatch
from os import path, walk
import shutil

from lib.utils.CMakeGenerator import CMakeGenerator
from lib.utils.DevTreeUtils import DevTree
from lib.utils.DirectoryUtils import ensure_exists
from lib.utils.Logger import Log
from lib.utils.ProcessUtils import ExecutableRunner


def execute_command(args):
    Log.info("Starting Glove dependency build...")
    Log.info("Using dependency sources from {0}".format(DevTree.deps_source_dir))
    Log.info("Installing dependencies into {0}".format(DevTree.deps_install_dir))

    # zlib
    Log.info("zlib Makefile generation...")
    zlib_source = path.join(DevTree.deps_source_dir, 'zlib')
    zlib_build = path.join(DevTree.deps_build_dir, 'zlib')
    zlib_install = path.join(DevTree.deps_install_dir, 'zlib')
    ensure_exists(zlib_build)
    ensure_exists(zlib_install)
    zlib_cmake = CMakeGenerator(zlib_source, zlib_build, {'CMAKE_INSTALL_PREFIX': zlib_install}, None, 'Release')
    zlib_cmake.run()

    Log.info("zlib make...")
    zlib_make = ExecutableRunner('make', ['-j8', 'clean', 'all', 'install'], zlib_build)
    zlib_make.run()

    # libPNG
    Log.info("libPNG Makefile generation...")
    libpng_source = path.join(DevTree.deps_source_dir, 'libpng')
    libpng_build = path.join(DevTree.deps_build_dir, 'libpng')
    libpng_install = path.join(DevTree.deps_install_dir, 'libpng')
    ensure_exists(libpng_build)
    ensure_exists(libpng_install)
    libpng_cmake = CMakeGenerator(libpng_source, libpng_build,
                                  {'CMAKE_INSTALL_PREFIX': libpng_install, 'ZLIB_ROOT:PATH': zlib_install,
                                   'ZLIB_INCLUDE_DIR:PATH': path.join(zlib_install, 'include'),
                                   'ZLIB_LIBRARY:FILEPATH': path.join(zlib_install, 'lib', 'libz.so')}, None, 'Release')
    libpng_cmake.run()

    Log.info("libPNG make...")
    libpng_make = ExecutableRunner('make', ['-j8', 'clean', 'all', 'install'], libpng_build)
    libpng_make.run()

    # tclap
    Log.info("Tclap header installation")
    tclap_source = path.join(DevTree.deps_source_dir, 'tclap')
    tclap_source_include = path.join(tclap_source, 'include')
    tclap_install = path.join(DevTree.deps_install_dir, 'tclap')
    tclap_install_include = path.join(tclap_install, 'include')
    ensure_exists(tclap_install_include)
    for root, directories, files in walk(tclap_source_include):
        for file in fnmatch.filter(files, '*.h'):
            source_file = path.join(root, file)
            destination_file = path.join(tclap_install_include, path.relpath(source_file, tclap_source_include))
            ensure_exists(path.dirname(destination_file))
            Log.info("Copying {0} to {1}".format(source_file, destination_file))
            shutil.copy(source_file, destination_file)

    # yaml-cpp
    Log.info("yaml-cpp Makefile generation...")
    yamlcpp_source = path.join(DevTree.deps_source_dir, 'yaml-cpp')
    yamlcpp_build = path.join(DevTree.deps_build_dir, 'yaml-cpp')
    yamlcpp_install = path.join(DevTree.deps_install_dir, 'yaml-cpp')
    ensure_exists(yamlcpp_build)
    ensure_exists(yamlcpp_install)
    yamlcpp_cmake = CMakeGenerator(yamlcpp_source, yamlcpp_build, {'CMAKE_INSTALL_PREFIX': yamlcpp_install}, None,
                                   'Release')
    yamlcpp_cmake.run()

    Log.info("yaml-cpp make...")
    yamlcpp_make = ExecutableRunner('make', ['-j8', 'clean', 'all', 'install'], yamlcpp_build)
    yamlcpp_make.run()

    # libZip
    Log.info("libZip Makefile generation...")
    libzip_source = path.join(DevTree.deps_source_dir, 'libzip')
    libzip_build = path.join(DevTree.deps_build_dir, 'libzip')
    libzip_install = path.join(DevTree.deps_install_dir, 'libzip')
    ensure_exists(libzip_build)
    ensure_exists(libzip_install)
    libzip_cmake = CMakeGenerator(libzip_source, libzip_build,
                                  {'CMAKE_INSTALL_PREFIX': libzip_install, 'ZLIB_ROOT:PATH': zlib_install,
                                   'ZLIB_INCLUDE_DIR:PATH': path.join(zlib_install, 'include'),
                                   'ZLIB_LIBRARY:FILEPATH': path.join(zlib_install, 'lib', 'libz.so')}, None,
                                  'Release')
    libzip_cmake.run()

    Log.info("libZip make...")
    libzip_make = ExecutableRunner('make', ['-j8', 'clean', 'all', 'install'], libzip_build)
    libzip_make.run()

