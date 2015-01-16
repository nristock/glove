from lib.utils.TermColors import AnsiColor


class Verbosity:
    ERROR = 0
    INFO = 1
    DEBUG = 2


class Log:
    num_separators = 20
    info_color = AnsiColor.make_foreground_code(AnsiColor.BLUE)
    error_color = AnsiColor.make_foreground_code(AnsiColor.RED, True)
    verbosity = Verbosity.INFO

    _reset_formatting = AnsiColor.reset_formatting()

    @classmethod
    def set_num_separators(cls, num_separators):
        cls.num_separators = num_separators

    @classmethod
    def set_info_color(cls, info_color):
        cls.info_color = info_color

    @classmethod
    def set_error_color(cls, error_color):
        cls.error_color = error_color

    @classmethod
    def set_verbosity(cls, verbosity):
        cls.verbosity = verbosity

    @classmethod
    def info(cls, msg):
        """
        Prints a formatted info message to stdout
        :param msg: The message to output
        """

        if cls._should_log(Verbosity.INFO):
            print(cls.colorize_message("{0}> {1}".format('_' * cls.num_separators, msg), cls.info_color))

    @classmethod
    def error(cls, msg):
        """
        Prints a formatted error message to stdout
        :param msg: The message to output
        """

        if cls._should_log(Verbosity.ERROR):
            print(cls.colorize_message("{0}> {1}".format('_' * cls.num_separators, msg), cls.error_color))

    @classmethod
    def debug(cls, msg):
        """
        Prints a formatted debug message to stdout
        :param msg: The message to output
        """

        if cls._should_log(Verbosity.DEBUG):
            print("{0}> {1}".format('_' * cls.num_separators, msg))

    @classmethod
    def colorize_message(cls, msg, color):
        """ Prepends color in front of msg and appends TermColors.ENDC at the end """
        return "{0}{1}{2}".format(color, msg, cls._reset_formatting)

    @classmethod
    def _should_log(cls, verbosity_level):
        """ Returns whether the given verbosity level should be logged """
        return cls.verbosity >= verbosity_level

    @classmethod
    def set_verbosity(cls, new_verbosity):
        cls.verbosity = new_verbosity

