import uuid


def execute_command(args):
    uid = uuid.uuid4()

    uuid_as_hex = [uid.hex[i:i+2] for i in range(0, len(uid.hex), 2)]
    print('{{ {0} }}'.format(', '.join(['0x{0}'.format(part) for part in uuid_as_hex])))
