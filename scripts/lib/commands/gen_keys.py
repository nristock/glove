import re
from os import path

from lib.utils.DevTreeUtils import DevTree
from lib.utils.Logger import Log


KT_AXIS = "FLOAT_AXIS"
KT_BUTTON = "BUTTON"

key_class = "Key"


class Key:
    def __init__(self, technical_name, type):
        self.technical_name = technical_name
        self.type = type

    def ToDeclaration(self):
        if not self.technical_name:
            return "\n"
        return "extern const {0} {1};\n".format(key_class, self.technical_name)

    def ToDefinition(self):
        if not self.technical_name:
            return "\n"
        return "const {0} {1}({2});\n".format(key_class, self.technical_name,
                                              "\"{0}\", Key::Type::{1}".format(self.technical_name, self.type))

    def IsBlank(self):
        return not bool(self.technical_name)


def blank():
    return Key("", KT_BUTTON)


keys = [
    Key("MouseX", KT_AXIS),
    Key("MouseY", KT_AXIS),
    Key("MouseScrollUp", KT_AXIS),
    Key("MouseScrollDown", KT_AXIS),

    blank(),

    Key("LeftMouseButton", KT_BUTTON),
    Key("RightMouseButton", KT_BUTTON),
    Key("MiddleMouseButton", KT_BUTTON),

    blank(),

    Key("A", KT_BUTTON),
    Key("B", KT_BUTTON),
    Key("C", KT_BUTTON),
    Key("D", KT_BUTTON),
    Key("E", KT_BUTTON),
    Key("F", KT_BUTTON),
    Key("G", KT_BUTTON),
    Key("H", KT_BUTTON),
    Key("I", KT_BUTTON),
    Key("J", KT_BUTTON),
    Key("K", KT_BUTTON),
    Key("L", KT_BUTTON),
    Key("M", KT_BUTTON),
    Key("N", KT_BUTTON),
    Key("O", KT_BUTTON),
    Key("P", KT_BUTTON),
    Key("Q", KT_BUTTON),
    Key("R", KT_BUTTON),
    Key("S", KT_BUTTON),
    Key("T", KT_BUTTON),
    Key("U", KT_BUTTON),
    Key("V", KT_BUTTON),
    Key("W", KT_BUTTON),
    Key("X", KT_BUTTON),
    Key("Y", KT_BUTTON),
    Key("Z", KT_BUTTON),

    blank(),

    Key("Zero", KT_BUTTON),
    Key("One", KT_BUTTON),
    Key("Two", KT_BUTTON),
    Key("Three", KT_BUTTON),
    Key("Four", KT_BUTTON),
    Key("Five", KT_BUTTON),
    Key("Six", KT_BUTTON),
    Key("Seven", KT_BUTTON),
    Key("Eight", KT_BUTTON),
    Key("Nine", KT_BUTTON),

    blank(),

    Key("NumPad0", KT_BUTTON),
    Key("NumPad1", KT_BUTTON),
    Key("NumPad2", KT_BUTTON),
    Key("NumPad3", KT_BUTTON),
    Key("NumPad4", KT_BUTTON),
    Key("NumPad5", KT_BUTTON),
    Key("NumPad6", KT_BUTTON),
    Key("NumPad7", KT_BUTTON),
    Key("NumPad8", KT_BUTTON),
    Key("NumPad9", KT_BUTTON),

    blank(),

    Key("NumLock", KT_BUTTON),

    blank(),

    Key("Divide", KT_BUTTON),
    Key("Multiply", KT_BUTTON),
    Key("Subtract", KT_BUTTON),
    Key("Add", KT_BUTTON),

    blank(),

    Key("F1", KT_BUTTON),
    Key("F2", KT_BUTTON),
    Key("F3", KT_BUTTON),
    Key("F4", KT_BUTTON),
    Key("F5", KT_BUTTON),
    Key("F6", KT_BUTTON),
    Key("F7", KT_BUTTON),
    Key("F8", KT_BUTTON),
    Key("F9", KT_BUTTON),
    Key("F10", KT_BUTTON),
    Key("F11", KT_BUTTON),
    Key("F12", KT_BUTTON),

    blank(),

    Key("BackSpace", KT_BUTTON),
    Key("Enter", KT_BUTTON),
    Key("Space", KT_BUTTON),
    Key("Tab", KT_BUTTON),

    blank(),

    Key("Escape", KT_BUTTON),
    Key("Pause", KT_BUTTON),
    Key("CapsLock", KT_BUTTON),
    Key("PageUp", KT_BUTTON),
    Key("PageDown", KT_BUTTON),
    Key("End", KT_BUTTON),
    Key("Home", KT_BUTTON),
    Key("ScrollLock", KT_BUTTON),

    blank(),

    Key("Left", KT_BUTTON),
    Key("Right", KT_BUTTON),
    Key("Up", KT_BUTTON),
    Key("Down", KT_BUTTON),

    blank(),

    Key("Insert", KT_BUTTON),
    Key("Delete", KT_BUTTON),

    blank(),

    Key("LeftShift", KT_BUTTON),
    Key("RightShift", KT_BUTTON),

    blank(),

    Key("LeftControl", KT_BUTTON),
    Key("RightControl", KT_BUTTON),

    blank(),

    Key("LeftAlt", KT_BUTTON),
    Key("RightAlt", KT_BUTTON),

    blank(),

    Key("LeftBracket", KT_BUTTON),
    Key("RightBracket", KT_BUTTON),
    Key("Backslash", KT_BUTTON),

    blank(),

    Key("Semicolon", KT_BUTTON),
    Key("Hyphen", KT_BUTTON),

    blank(),

    Key("Comma", KT_BUTTON),
    Key("Period", KT_BUTTON),
    Key("Slash", KT_BUTTON),
]


def execute_command(args):
    Log.info("Generating input keys...")

    header = args.header
    implementation = args.implementation

    generate_regex = re.compile(r"(// \[GENERATE:KEYS\]\n)(.*)(// \[\\GENERATE:KEYS\])", re.M | re.S)

    num_keys = 0
    declarations = "\g<1>"
    definitions = "\g<1>"
    for key in keys:
        declarations += key.ToDeclaration()
        definitions += key.ToDefinition()

        if not key.IsBlank():
            num_keys += 1

    declarations += "\g<3>"
    definitions += "\g<3>"

    # Generate declarations in header
    new_header_content = ""
    with open(header, 'r') as header_file:
        new_header_content = generate_regex.sub(declarations, header_file.read())
    with open(header, 'w+') as header_file:
        header_file.write(new_header_content)

    # Generate definitions in cc file
    new_cc_content = ""
    with open(implementation, 'r') as cc_file:
        new_cc_content = generate_regex.sub(definitions, cc_file.read())
    with open(implementation, 'w+') as cc_file:
        cc_file.write(new_cc_content)

    Log.info("Generated {0} input keys".format(num_keys))


def setup_args(parser):
    parser.add_argument('--header', type=str, default=path.join(DevTree.source_dir, 'glove/input/Keys.hpp'),
                        help="The header to generate the key declarations into")
    parser.add_argument('--implementation', '--impl', type=str,
                        default=path.join(DevTree.source_dir, 'glove/input/Keys.cc'),
                        help="The source file to generate the key definitions into")

