import os

VariantDir('build', 'tests', duplicate=False)
env = Environment(
	CPPPATH=['./include', './doctest/doctest'],
	CXXFLAGS='-g -Wall -std=c++17'
)
env['ENV']['TERM'] = os.environ['TERM'] # Colored output

env.Program( "test", [ Glob("build/*.cc") ] )
