#!/usr/bin/python

import argparse
import pystache as pst
import os
import sys

argParser = argparse.ArgumentParser()
argParser.add_argument('class_name', metavar='class_name', type=str, help='The new class\' name')
argParser.add_argument('base_classes', metavar='base_classes', type=str, nargs='*', help='')
argParser.add_argument('-ht', '--headertemplate', type=str, default='templates/PyBinding.h.mustache')
argParser.add_argument('-ct', '--sourcetemplate', type=str, default='templates/PyBinding.cpp.mustache')
argParser.add_argument('-a', '--addtogit', type=bool, default=True)

args = argParser.parse_args()

classNameParts = args.class_name.split('/')
classPath = classNameParts[:-1]
className = classNameParts[-1]


fileBase = '/'.join(classPath);
classHeaderFile = fileBase + '/' + className + '.h'
bindingHeaderFile = 'src/scripting/modules/glove/Py' + className + '.h';
bindingSourceFile = 'src/scripting/modules/glove/Py' + className + '.cpp';

if(not os.path.exists('src/' + classHeaderFile)):
	print('Class header does not exist')
	sys.exit(1)

if(os.path.exists(bindingHeaderFile)):
	print('Header already exists')
	sys.exit(1)

if(os.path.exists(bindingSourceFile)):
	print('Source file already exists')
	sys.exit(1)

hasBaseClasses = len(args.base_classes) > 0

mustacheData = {
	'class_header' : classHeaderFile,
	'class_name' : className,
	'has_bases' : hasBaseClasses,
	'base_classes' : ', '.join(args.base_classes),
	'protection_define' : 'SCRIPTING_MODULES_GLOVE_PY' + className.upper() + '_H_'
}

mustRenderer = pst.Renderer()
headerContent = mustRenderer.render_path(args.headertemplate, mustacheData)
sourceContent = mustRenderer.render_path(args.sourcetemplate, mustacheData)

headerFileHandle = open(bindingHeaderFile, 'w')
headerFileHandle.write(headerContent.replace('\r\n', '\n'))
headerFileHandle.close()

sourceFileHandle = open(bindingSourceFile, 'w')
sourceFileHandle.write(sourceContent.replace('\r\n', '\n'))
sourceFileHandle.close()