#!/usr/bin/python
# Page 157

import optparse
p = optparse.OptionParser()

# An option taking an argument
p.add_option("-o", action="store", dest="outfile")
p.add_option("--output", action="store", dest="outfile")

# An option that sets a boolean flag
p.add_option("-d", action="store_true", dest="debug")
p.add_option("--debug", action="store_true", dest="debug")

# Set default values for selected options
p.set_defaults(debug=False)

# Parse the command line
opts, args = p.parse_args()

# Retrieve the option settings
outfile   = opts.outfile
debugmode = opts.debug
