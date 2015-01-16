import subprocess

from lib.utils.Logger import Log


class ExecutableRunner:
    def __init__(self, executable_name, arguments=None, working_dir='.',
                 on_success=lambda: (Log.info("Execution successful")),
                 on_failure=lambda: (Log.error("Execution failed"))):
        if not executable_name:
            raise RuntimeError('executable_name argument not set')

        self.executable_name = executable_name
        self.arguments = arguments if arguments else list()
        self.working_dir = working_dir
        self.on_success = on_success
        self.on_failure = on_failure

    def run(self):
        command = [self.executable_name] + self.arguments

        Log.info('Running {0}...'.format(' '.join(command)))
        proc = subprocess.Popen(command, stderr=subprocess.STDOUT, cwd=self.working_dir)
        proc.communicate()

        if proc.returncode == 0:
            self.on_success()
            return True
        else:
            self.on_failure()
            return False
