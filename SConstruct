import os

def make_package(env, tag, package) :
    objs = SConscript(os.path.join(package,"SConscript"), exports={'env' : env, 'tag' :  tag})
    return objs






paths =  ' -Iinclude '
libs = Split( ' -lXrandr -lXi -lpthread -lXxf86vm -lX11 -lGL -lGLU -lGLEW -lglfw3 ' )

#debug options
debug = Environment(ENV = {'PATH' : os.environ['PATH']})
debug['CXX'] = 'g++-4.8'
debug['CXXFLAGS'] = '-Wall -std=c++1y -O0 -g -fPIE' + paths
debug.Append( LINKFLAGS = Split(' -fPIE') )

#release options
release = Environment(ENV = {'PATH' : os.environ['PATH']})
release['CXX'] = 'g++-4.8'
release['CXXFLAGS'] = '-Wall -std=c++1y -O3 -fPIE -flto' + paths
release.Append( LINKFLAGS = Split(' -O3 -flto -fPIE') )


#profiling options
profile = Environment(ENV = {'PATH' : os.environ['PATH']})
profile['CXX'] = 'g++-4.8'
profile['CXXFLAGS'] = '-Wall -std=c++1y -fPIE  -pg -g' + paths
profile.Append( LINKFLAGS = Split(' -fPIE -pg') )





#targets
d_objs = make_package(debug, 'dbg', 'src')
d_target = debug.Program('lander-dbg', d_objs, LIBS=libs, LIBPATH='lib')

r_objs = make_package(release, 'rel', 'src')
r_target = release.Program('lander', r_objs, LIBS=libs, LIBPATH='lib')

p_objs = make_package(profile, 'prof', 'src')
p_target = profile.Program('lander-profile', p_objs, LIBS=libs, LIBPATH='lib')

Default(d_target)
