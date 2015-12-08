import libxml2
import libxslt
import yaml
import os
import glob

# TODO Header template
# TODO Header decorator

print("=== PyDia2Code C++ Header-only generator === ")
print("By Timothe PEREZ | 3IS 2015 @ ENSEA | www.ensea.fr")

print("= Step 0 : Initialization")
file = file("config.yml", "r")
config = yaml.load(file)

print("Generating Headers for " + config["project"]["name"] +
      " version " + config["project"]["version"])


# Conf
tmp_folder = config["directories"]["temp"]
inp_folder = config["directories"]["input"]
out_folder = config["directories"]["output"]
#

print("Cleaning folders...")
for namespace in config["namespaces"]:
    for f in glob.glob(out_folder + namespace + "/*.h"):
        os.unlink(f)
print("Done")
# input("Wait")
print("= Step 1 : extracting data from DIA file (Non Gzipped!)")
styledoc = libxml2.parseFile("dia-uml.xsl")
style = libxslt.parseStylesheetDoc(styledoc)
for namespace in config["namespaces"]:
    try:
        doc = libxml2.parseFile(inp_folder + "diagram_" + namespace + ".dia")
        result = style.applyStylesheet(doc, None)
        style.saveResultToFilename(tmp_folder + namespace + ".xml", result, 0)
        print(namespace + " : Dia2XML OK")
    except:
        print(namespace + " : Fail at Dial2XML")
        print(namespace + " : Is the dia file NOT gzipped?")

style.freeStylesheet()
doc.freeDoc()
result.freeDoc()

print("= Step 2 : creating headers files from XML")
styledoc = libxml2.parseFile("dia-uml2cpp.xsl")
style = libxslt.parseStylesheetDoc(styledoc)

for namespace in config["namespaces"]:
    try:
        print("Headers for namespace " + namespace)
        params = {'directory': repr(out_folder + namespace + "/")}

        doc = libxml2.parseFile(tmp_folder + namespace + ".xml")
        result = style.applyStylesheet(doc, params)
        # style.saveResultToFilename("engine", result, 0)
        print(namespace + " : XML2CPP OK")
    except:
        print(namespace + " : Fail at XML2CPP")

print("Warning, XLST lib can fail even if no exception is thrown.")
print("Make sure your headers are correctly generated")

exit(0)