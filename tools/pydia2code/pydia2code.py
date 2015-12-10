#!/usr/bin/python3
import lxml.etree as etree
import yaml
import os
import glob
import datetime

# TODO Exceptions proper handling
# TODO Python 3

print("=== PyDia2Code C++ Header-only generator === ")
print("Version 1.0.0 | Python 3.4")
print("By Timothe Perez | 3IS 2015 @ ENSEA | www.ensea.fr")

print("= Step 0 : Initialization")
file = open("config.yml", "r")
config = yaml.load(file)

print("Generating Headers for " + config["project"]["name"] +
      " version " + config["project"]["version"])


# Conf
tmp_folder = config["directories"]["temp"]
inp_folder = config["directories"]["input"]
out_folder = config["directories"]["output"]
dia2xml = config["stylesheets"]["dia2xml"]
xml2cpp = config["stylesheets"]["xml2cpp"]
#
# Prerun checks
print("Checking folders existence")
if not os.path.exists(tmp_folder):
    print("TMP folder not found. Creating")
    os.mkdir(tmp_folder)
if not os.path.exists(out_folder):
    print("Output folder not found. Creating")
    os.mkdir(out_folder)
for namespace in config["namespaces"]:
    if not os.path.exists(out_folder + namespace + "/"):
        print("Output folder for " + namespace + " not found. Creating")
        os.mkdir(out_folder + namespace + "/")
if not os.path.exists(inp_folder):
    raise IOError("Input folder not found")

print("Cleaning folders...")
for namespace in config["namespaces"]:
    for f in glob.glob(out_folder + namespace + "/*.hpp"):
        os.unlink(f)

# Now running : first transformation DIA -> custom XML
print("= Step 1 : extracting data from DIA file (Non Gzipped!)")
styledoc = etree.parse(dia2xml)
style = etree.XSLT(styledoc)
for namespace in config["namespaces"]:
    try:
        doc = etree.parse(inp_folder + "diagram_" + namespace + ".dia")
        result = style(doc)
        # Adding specific decorators (from config file)
        print(namespace + " : Adding decorators data")
        root = result.getroot()
        decorators = etree.SubElement(root, "decorators")
        if namespace in config["decorators"]:

            # for each class in namespace
            if config["decorators"][namespace]:
                for class_name in config["decorators"][namespace]:
                    dec = etree.Element("class", name=class_name)
                    decorators.append(dec)
                    class_node = config["decorators"][namespace][class_name]
                    # includes
                    if "include" in class_node:
                        for include in class_node["include"]:
                            dec.append(etree.Element("include", value=include))
        print(namespace + " : Saving tmp xml file")
        f = open(tmp_folder + namespace + ".xml", "w")
        f.write(str(result))
            #style.saveResultToFilename(tmp_folder + namespace + ".xml", result, 0)
        f.close()
        print(namespace + " : Dia2XML OK")
    except IOError:
         print(namespace + " : Fail at Dial2XML")
         print(namespace + " : Is the dia file NOT gzipped or even exists?")




print("= Step 2 : creating headers files from XML")
styledoc = etree.parse(xml2cpp)
style = etree.XSLT(styledoc)
# Global Infos
params = {"project": repr(config["project"]["name"]),
          "author": repr(config["author"]),
          "version": repr(config["project"]["version"]),
          "date": repr(datetime.datetime.now().strftime("%Y-%m-%d %H:%M"))}
for namespace in config["namespaces"]:
    try:
        print("Headers for namespace " + namespace)
        params["directory"] = repr(out_folder + namespace + "/")
        params["include"] = repr(config["includes"][namespace])

        doc = etree.parse(tmp_folder + namespace + ".xml")
        result = style(doc, **params)
        print(namespace + " : XML2CPP OK")
    except IOError:
        print(namespace + " : Fail at XML2CPP (IOError)")

print("C++ Headers should be generated in " + out_folder)
print("Job's done!")
exit(0)
