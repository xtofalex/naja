#...
extensions = [
  "breathe",
  'sphinx_rtd_theme',
]
#...

html_theme = "sphinx_rtd_theme"

breathe_default_project = "naja"

import subprocess
#call doxygen from cmake
subprocess.call('mkdir build', shell=True)
subprocess.call('cd build; cmake ../.. -DBUILD_ONLY_DOC=ON', shell=True)
subprocess.call('cd build; make docs', shell=True)

breathe_projects = { "naja" : "./build/xml/" }
breathe_default_project = "naja"