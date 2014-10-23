#!/usr/bin/python

import argparse
import pystache as pst
import os
import sys

argParser = argparse.ArgumentParser()
argParser.add_argument('class_name', metavar='class_name', type=str, help='The new class\' name. (e.g. core/MyComponent)')
argParser.add_argument('-ht', '--headertemplate', type=str, default='templates/DerivedFromGloveObject.h.mustache')
argParser.add_argument('-ct', '--sourcetemplate', type=str, default='templates/DerivedFromGloveObject.cpp.mustache')
argParser.add_argument('-tt', '--testtemplate', type=str, default='templates/GTestFixture.cpp.mustache')
argParser.add_argument('-p', '--profilable', type=bool, default=True, help='Wether to make this class profilable or not')
argParser.add_argument('-d', '--derive-from-glove-object', type=bool, default=True, help='Derive new class from GloveObject?')
argParser.add_argument('-t', '--create-tests', type=bool, default=True, help='Create tests?')
argParser.add_argument('-a', '--addtogit', type=bool, default=True, help='Add created files to git')

args = argParser.parse_args()

classNameParts = args.class_name.split('/')
classPath = classNameParts[:-1]
className = classNameParts[-1]

includePath = '/'.join(classPath)
fileBase = 'src/' + includePath;
headerFile = fileBase + '/' + className + '.h'
sourceFile = fileBase + '/' + className + '.cpp' 

testFileBase = 'src/tests/' + includePath
testFile = fileBase + '/' + className + '.cpp'

if(os.path.exists(headerFile)):
	print('Header already exists')
	sys.exit(1)

if(os.path.exists(sourceFile)):
	print('Source file already exists')
	sys.exit(1)

if(args.create_tests and os.path.exists(testFile)):
	print('Test source file already exists')
	sys.exit(1)

mustacheData = {
	'class_name' : className,
	'include_path' : includePath,
	'profilable' : args.profilable,
	'derive_from_glove_object' : args.derive_from_glove_object
}

mustRenderer = pst.Renderer()
headerContent = mustRenderer.render_path(args.headertemplate, mustacheData)
sourceContent = mustRenderer.render_path(args.sourcetemplate, mustacheData)
testContent = mustRenderer.render_path(args.testtemplate, mustacheData)

if(not os.path.exists(fileBase)):
	print('Creating dirs')
	os.makedirs(fileBase)

headerFileHandle = open(headerFile, 'w')
headerFileHandle.write(headerContent.replace('\r\n', '\n'))
headerFileHandle.close()

sourceFileHandle = open(sourceFile, 'w')
sourceFileHandle.write(sourceContent.replace('\r\n', '\n'))
sourceFileHandle.close()

if(args.create_tests):
	if(not os.path.exists(testFileBase)):
		os.makedirs(testFileBase)

	testFileHandle = open(testFile, 'w')
	testFileHandle.write(testContent.replace('\r\n', '\n'))
	testFileHandle.close()
