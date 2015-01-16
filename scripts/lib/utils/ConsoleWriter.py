import sys


class ConsoleWriter:
    lineWidth = 70
    primarySectionHeader = '=' * lineWidth
    secondarySectionHeader = '-' * lineWidth
    horizontalSeparator = '|'

    @staticmethod
    def WritePrimarySectionHeader():
        print('\n+{0}+'.format(ConsoleWriter.primarySectionHeader))

    @staticmethod
    def WriteSecondarySectionHeader():
        print('+{0}+'.format(ConsoleWriter.secondarySectionHeader))

    @staticmethod
    def WritePrimarySectionFooter():
        print('+{0}+\n'.format(ConsoleWriter.primarySectionHeader))

    @staticmethod
    def WriteSecondarySectionFooter():
        print('+{0}+\n'.format(ConsoleWriter.secondarySectionHeader))

    @staticmethod
    def WriteInfo(msg, component=''):
        print('{0}{1}'.format(
            '[{0}] '.format(component) if component else '',
            msg
        ))

    @staticmethod
    def SplitMessage(msg, lineLength):
        lines = []

        for start in range(0, len(msg), lineLength):
            lines.append(msg[start:start+lineLength])

        return lines

    @staticmethod
    def WriteBorderedLine(msg):
        sys.stdout.write('| ' + msg)
        sys.stdout.write(' ' * (ConsoleWriter.lineWidth - len(msg) - 2))
        sys.stdout.write(' |')
        print()

    @staticmethod
    def PrintTable(data, printSeparators=False):
        numLines = len(data)

        if numLines == 0:
            return

        numColumns = len(data[0])
        usableLineWidth = float(ConsoleWriter.lineWidth - numColumns*3 + 1)

        absoluteColumnWidths = [0] * numColumns
        for line in data:
            for column in range(numColumns):
                absoluteColumnWidths[column] = len(line[column]) if len(line[column]) > absoluteColumnWidths[column] else absoluteColumnWidths[column]

        maximumAbsoluteColumnWidth = sum(absoluteColumnWidths)
        normalizedColumnWidths = [0] * numColumns
        for column in range(numColumns):
            normalizedColumnWidths[column] = int((float(absoluteColumnWidths[column]) / float(maximumAbsoluteColumnWidth)) * usableLineWidth)

        normalizedColumnWidthSum = sum(normalizedColumnWidths)

        if printSeparators:
            ConsoleWriter.WriteSecondarySectionHeader()

        for line in data:
            outLine = ''
            for column in range(numColumns):
                currentText = line[column]

                outLine += '| '
                outLine += currentText
                outLine += ' ' * max((normalizedColumnWidths[column] - len(currentText) + 1), 1)
            outLine += ' ' * int(usableLineWidth - normalizedColumnWidthSum) + '|'

            print(outLine)

        if printSeparators:
            ConsoleWriter.WriteSecondarySectionFooter()
