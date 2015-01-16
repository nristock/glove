_escape = '\033['
_sgr_background_offset = 10
_sgr_base_normal = 30
_sgr_base_bright = 90


class AnsiColor:
    BLACK = 0
    RED = 1
    GREEN = 2
    YELLOW = 3
    BLUE = 4
    MAGENTA = 5
    CYAN = 6
    WHITE = 7

    @staticmethod
    def make_foreground_code(color, bold=False, bright=True):
        return _escape + str((_sgr_base_bright if bright else _sgr_base_normal) + color) + (';1' if bold else '') + 'm'

    @staticmethod
    def make_background_code(color, bold=False, bright=True):
        return _escape + str((_sgr_base_bright if bright else _sgr_base_normal) + _sgr_background_offset + color) + (
            ';1' if bold else '') + 'm'

    @staticmethod
    def reset_formatting():
        return _escape + '0m'
