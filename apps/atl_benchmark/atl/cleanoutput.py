
import re
import subprocess

# pull file into a string variable in this script
with open('gen.out','r') as genF:
  orig_contents = genF.read()


# First set of rewrites substitute various local
# characters/patterns with what they were meant to be

# convert newline literals to real newlines
real_newlines   = re.sub(r'\\n','\n',orig_contents)
# then remove gratuitous quotes
no_quotes       = re.sub(r'"','',real_newlines)
# and convert '@' into '"' to resolve the actually desired quotes
at_quotes       = re.sub(r'@','"',no_quotes)
# likewise use '~' as a proxy for newline literals
tilde_newlines  = re.sub(r'~','\\n',at_quotes)

subbed_file = tilde_newlines

# for debugging
#print(subbed_file)



# having cleaned up the string, now we break it into files

# split the file into constituent files
# every file is prefixed by !!!, so ignore anything
# before the first !!!
files           = subbed_file.split('!!!\n')[1:]

for f in files:
  # the first line of the file is the name of the file to write out
  filename, bodytext = f.split('\n',1)

  # write the file out
  with open(filename,'w') as F:
    F.write(bodytext)

  # format the written file
  subprocess.run(["indent","-i2","-nut",filename])

