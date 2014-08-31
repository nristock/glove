#!/usr/bin/python

import argparse
import pystache as pst
import os
import sys

argParser = argparse.ArgumentParser()
argParser.add_argument('class_name', metavar='class_name', type=str, help='The new class\' name')
argParser.add_argument('-ht', '--headertemplate', type=str, default='templates/DerivedFromGloveObject.h.mustache')
argParser.add_argument('-ct', '--sourcetemplate', type=str, default='templates/DerivedFromGloveObject.cpp.mustache')
argParser.add_argument('-a', '--addtogit', type=bool, default=True)

args = argParser.parse_args()

classNameParts = args.class_name.split('/')
classPath = classNameParts[:-1]
className = classNameParts[-1]


fileBase = 'src/' + '/'.join(classPath);
headerFile = fileBase + '/' + className + '.h'
sourceFile = fileBase + '/' + className + '.cpp'

if(os.path.exists(headerFile)):
	print('Header already exists')
	sys.exit(1)

if(os.path.exists(sourceFile)):
	print('Source file already exists')
	sys.exit(1)

mustacheData = {
	'class_name' : className,
	'protection_define' : '_'.join(classNameParts).upper() + '_H_' 
}

mustRenderer = pst.Renderer()
headerContent = mustRenderer.render_path(args.headertemplate, mustacheData)
sourceContent = mustRenderer.render_path(args.sourcetemplate, mustacheData)

if(not os.path.exists(fileBase)):
	print('Creating dirs')
	os.makedirs(fileBase)

headerFileHandle = open(headerFile, 'w')
headerFileHandle.write(headerContent.replace('\r\n', '\n'))
headerFileHandle.close()

sourceFileHandle = open(sourceFile, 'w')
sourceFileHandle.write(sourceContent.replace('\r\n', '\n'))
sourceFileHandle.close()