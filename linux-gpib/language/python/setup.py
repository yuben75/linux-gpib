#!/usr/bin/env python

from distutils.core import setup,Extension
setup(name="gpib",
	version="1.0",
	description="Linux GPIB Python Bindings",
	py_modules = ['language/python/Gpib'],
	ext_modules=[
		Extension("gpib",
		["language/python/gpibinter.c"],
		include_dirs=["include"],
		library_dirs = ['lib/.libs'],
		libraries=["gpib", "pthread"]
	)]
)
