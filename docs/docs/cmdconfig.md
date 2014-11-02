# Command Line Options and Configuration

`GloveCore::GloveCore(int, char**)` will parse command line options and load the primary engine configuration file (defaults to data/glove.json).

All configuration options can be set using the config file and most options are also available though the command line options.
Options specified on the command line will override whatever is specified in the config file.


## window-width

**Description:** Main window's width<br/>
**JSON path:** rendering.window.width<br/>
**Type:** int<br/>
**Required:** No<br/>
**Default:** 800<br/>


## window-height

**Description:** Main window's height<br/>
**JSON path:** rendering.window.height<br/>
**Type:** int<br/>
**Required:** No<br/>
**Default:** 600<br/>


## opengl-version-major

**Description:** OpenGL major version to request<br/>
**JSON path:** rendering.opengl.major<br/>
**Type:** int<br/>
**Required:** No<br/>
**Default:** 3<br/>


## opengl-version-minor

**Description:** OpenGL minor version to request<br/>
**JSON path:** rendering.opengl.minor<br/>
**Type:** int<br/>
**Required:** No<br/>
**Default:** 3<br/>


## init-rendering

**Description:** Whether to initialize the rendering system<br/>
**JSON path:** engine.subsystems.init["rendering"]<br/>
**Type:** bool (array entry in JSON) <br/>
**Required:** No<br/>
**Default:** 1 (true)<br/>


## init-scripting

**Description:** Whether to initialize the scripting system<br/>
**JSON path:** engine.subsystems.init["scripting"]<br/>
**Type:** bool (array entry in JSON) <br/>
**Required:** No<br/>
**Default:** 1 (true)<br/>ion
