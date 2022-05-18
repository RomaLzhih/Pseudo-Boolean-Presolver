import sys
import os
import bz2
from bz2 import decompress
subfolder = "otheropt/"

for path, subdirs, files in os.walk(subfolder):
    for name in files:
        filepath = os.path.join(path, name)
        newfilepath = filepath[:filepath.rfind('.bz2')]
        with open(newfilepath, 'wb') as new_file, bz2.BZ2File(filepath, 'rb') as file:
            for data in iter(lambda: file.read(100 * 1024), b''):
                new_file.write(data)
