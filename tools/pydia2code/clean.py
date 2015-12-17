#!/usr/bin/python
import lxml.etree as etree
import yaml
import os
import glob
import datetime

file = open("config.yml", "r")
config = yaml.load(file)

# Conf
tmp_folder = config["directories"]["temp"]
inp_folder = config["directories"]["input"]
out_folder = config["directories"]["output"]

print("Cleaning folders...")
for namespace in config["namespaces"]:
    for f in glob.glob(out_folder + namespace + "/*.hpp"):
        os.unlink(f)
