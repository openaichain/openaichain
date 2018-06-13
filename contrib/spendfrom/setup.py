from distutils.core import setup
setup(name='OACCspendfrom',
      version='1.0',
      description='Command-line utility for oaccoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@oaccoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
