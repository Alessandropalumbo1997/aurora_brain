## ! DO NOT MANUALLY INVOKE THIS setup.py, USE CATKIN INSTEAD

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['brain'],
    package_dir={'': 'src'},
    scripts=['bin/dopamine', 'bin/cortisol', 'bin/epinephrine', 'bin/oxytocin', 'bin/hormone_receptor', 'bin/auditory_association_cortex', 'bin/visual_association_cortex', 'bin/amygdala']
)

setup(**setup_args)
