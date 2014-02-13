#!/usr/bin/python

import re
import string
import os
import os.path

PY_SUFFICES = ( ".py", ".pyc" )
CPP_SUFFICES = ( ".c", ".cc", ".cpp", ".h", ".hpp", ".tpp" )
CODE_SUFFICES = PY_SUFFICES + CPP_SUFFICES

class Foo:
	pass

def cpp_counter( code_str ):
	code_str = re.sub( r"(''|'[^\\]'|'\\.')", "", code_str )
	code_str = re.sub( r'(""|"(?:[^\\"]|\\")*")', "", code_str )
	code_str = re.sub( r"(//[^\n]*\n)", "", code_str )
	code_str = re.sub( r"(/\*(?:.|\n)*?\*/)", "", code_str )
	
	return code_str.count( ';' )

def py_counter( code_str ):
	return len( [ line \
				for line in re.sub( r'(""".*?""")', "", code_str ).split( '\n' ) \
				if not all( c in string.whitespace for c in line ) \
				and line[-1] != '\\' ] )
	
def countLOC( filename ):
	with open( filename, "r" ) as f:
		if any( filename.endswith( suffix ) for suffix in PY_SUFFICES ):
			return py_counter( f.read() )
		elif any( filename.endswith( suffix ) \
			 for suffix in CPP_SUFFICES ):
			return cpp_counter( f.read() )
		else:
			return None

def crawl( top ):
	nLines = {}
	for dirpath, dirnames, filenames in os.walk( top ):
		for filename in filenames:
			if any( filename.endswith( suffix ) for suffix in CODE_SUFFICES ):
				nLines[ filename ] = countLOC( os.path.join( dirpath, filename ) )
	
	return nLines

if __name__ == '__main__':
	import sys
	
	try:
		if len( sys.argv ) == 1:
			nLines = crawl( os.getcwd() )
		elif any( sys.argv[1].endswith( suffix ) for suffix in CODE_SUFFICES ):
			nLines = { sys.argv[1] : countLOC( sys.argv[1] ) }
		else:
			nLines = crawl( os.path.abspath( sys.argv[1] ) )
		
		if len( nLines ) <= 10:
			for i, lines in nLines.iteritems():
				print i, lines
			if len( nLines ) != 1:
				print "Total:", sum( nLines.itervalues() )
		else:
			with open( "lines.txt", "w" ) as f:
				f.writelines( "{} {}".format( i, lines ) for i, lines in nLines.iteritems() )
				print "Total:", sum( nLines.itervalues() )
				print "Details written to lines.txt"
	except OSError as e:
		print e
