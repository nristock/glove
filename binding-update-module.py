#!/usr/bin/python

import argparse
import pystache as pst
import os
import sys
import glob
import re

baseDir = os.getcwd()

argParser = argparse.ArgumentParser()
argParser.add_argument('-ht', '--headertemplate', type=str, default=baseDir + '/templates/PyGloveModule.h.mustache')
argParser.add_argument('-ct', '--sourcetemplate', type=str, default=baseDir + '/templates/PyGloveModule.cpp.mustache')
args = argParser.parse_args()

moduleBase = 'src/scripting/modules/glove'

os.chdir(moduleBase)

classNames = []
classFiles = glob.glob('Py*.h')
for cFile in classFiles:
	classNames.append(re.sub(r'^Py', '', cFile).replace('.h', ''))
	print('Exporting ' + classNames[-1])

moduleHeaderFile = 'GloveModule.h';
moduleSourceFile = 'GloveModule.cpp';

mustacheData = {
	'class_names' : classNames
}

mustRenderer = pst.Renderer()
headerContent = mustRenderer.render_path(args.headertemplate, mustacheData)
sourceContent = mustRenderer.render_path(args.sourcetemplate, mustacheData)

headerFileHandle = open(moduleHeaderFile, 'w')
headerFileHandle.write(headerContent.replace('\r\n', '\n'))
headerFileHandle.close()

sourceFileHandle = open(moduleSourceFile, 'w')
sourceFileHandle.write(sourceContent.replace('\r\n', '\n'))
sourceFileHandle.close()