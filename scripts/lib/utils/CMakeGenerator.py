from os import name as os_name

from lib.utils.ProcessUtils import ExecutableRunner
from lib.utils.Logger import Log


class CMakeGenerator:
    def __init__(self, source_dir, build_dir, definitions=None, make_file_generator=None, build_type='Debug'):
        if not source_dir:
            raise RuntimeError('source_dir argument not set')

        if not build_dir:
            raise RuntimeError('build_dir argument not set')

        self.source_dir = source_dir
        self.build_dir = build_dir
        self.definitions = definitions if definitions else dict()
        self.build_type = build_type

        if make_file_generator is None:
            if os_name is 'nt':
                self.make_file_generator = 'Visual Studio 12 2013 Win64'
            elif os_name is 'posix':
                self.make_file_generator = 'Unix Makefiles'

        else:
            self.make_file_generator = make_file_generator

    def add_definition(self, name, value):
        self.definitions += {name: value}

    def run(self):
        definitions_command_line_args = []
        for name, value in self.definitions.items():
            definitions_command_line_args += ['-D{0}={1}'.format(name, value)]

        definitions_command_line_args += ['-DCMAKE_BUILD_TYPE={0}'.format(self.build_type)]

        command_runner = ExecutableRunner('cmake', definitions_command_line_args + ['-G', self.make_file_generator] + [self.source_dir],
                                          self.build_dir,
                                          lambda: (Log.info("Successfully generated makefiles")),
                                          lambda: (Log.error("Makefile generation failed")))

        command_runner.run()
